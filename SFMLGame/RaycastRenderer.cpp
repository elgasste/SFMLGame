#include <math.h>
#include <cassert>
#include <SFML/Graphics/PrimitiveType.hpp>

#include "RaycastRenderer.h"
#include "GameConfig.h"
#include "Entity.h"
#include "SFMLWindow.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

RaycastRenderer::RaycastRenderer( shared_ptr<GameConfig> config,
                                  shared_ptr<Entity> player,
                                  shared_ptr<SFMLWindow> window ) :
   _config( config ),
   _player( player ),
   _window( window )
{
   // MUFFINS: these should go in a render config somewhere
   _wallHeight = 100.0f;
   _projectionPlaneDelta = config->ScreenHeight / 1.5f;

   auto screenWidth = (float)config->ScreenWidth;
   auto screenHeight = (float)config->ScreenHeight;

   _ceilingRenderRect[0] = Vertex( Vector2f( 0, 0 ), Color( 128, 128, 128 ) );
   _ceilingRenderRect[1] = Vertex( Vector2f( screenWidth, 0 ), Color( 128, 128, 128 ) );
   _ceilingRenderRect[2] = Vertex( Vector2f( screenWidth, screenHeight / 2.0f ), Color::Black );
   _ceilingRenderRect[3] = Vertex( Vector2f( 0, screenHeight / 2.0f ), Color::Black );

   _floorRenderRect[0] = Vertex( Vector2f( 0, screenHeight / 2.0f ), Color::Black );
   _floorRenderRect[1] = Vertex( Vector2f( screenWidth, screenHeight / 2.0f ), Color::Black );
   _floorRenderRect[2] = Vertex( Vector2f( screenWidth, screenHeight ), Color( 128, 128, 128 ) );
   _floorRenderRect[3] = Vertex( Vector2f( 0, screenHeight ), Color( 128, 128, 128 ) );
}

void RaycastRenderer::RenderCeilingAndFloor()
{
   _window->Draw( _ceilingRenderRect, 4, Quads );
   _window->Draw( _floorRenderRect, 4, Quads );
}

void RaycastRenderer::RenderLineseg( const Lineseg& lineseg,
                                     float drawStartAngle,
                                     int startColumn,
                                     int endColumn )
{
   auto playerPosition = _player->GetPosition();
   auto playerAngle = _player->GetAngle();

   for ( int i = startColumn; i <= endColumn; i++ )
   {
      Vector2f pIntersect;
      auto doesIntersect = Geometry::RayIntersectsLine( playerPosition, drawStartAngle, lineseg.start.x, lineseg.start.y, lineseg.end.x, lineseg.end.y, &pIntersect );

      // MUFFINS: what should we do if this doesn't work?
      // 
      // apparently this returns false on the far left edge, so... what if we passed in the far left intersection point as a parameter?
      // I don't know why this doesn't work though, that's probably a bigger question.
      assert( doesIntersect );

      // from the Wolfenstein 3D book. it's supposed to fix fish-eye, but sometimes it seems to cause reverse-fish-eye
      //
      // MUFFINS: move this into the Geometry utility
      auto rayLength = ( ( pIntersect.x - playerPosition.x ) * cosf( playerAngle ) ) - ( ( pIntersect.y - playerPosition.y ) * sinf( playerAngle ) );

      // this uses the formula ProjectedWallHeight = ( ActualWallHeight / DistanceToWall ) * DistanceToProjectionPlane
      auto projectedWallHeight = ( ( _wallHeight / rayLength ) * _projectionPlaneDelta );

      auto columnIndex = i * 2;
      auto color = lineseg.linedef->color;

      _renderColumns[columnIndex].color = lineseg.linedef->color;
      _renderColumns[columnIndex + 1].color = color;
      _renderColumns[columnIndex].position.x = (float)i;
      _renderColumns[columnIndex].position.y = ( _config->ScreenHeight / 2.0f ) - ( projectedWallHeight / 2.0f );
      _renderColumns[columnIndex + 1].position.x = (float)i;
      _renderColumns[columnIndex + 1].position.y = ( _config->ScreenHeight / 2.0f ) + ( projectedWallHeight / 2.0f );

      _window->Draw( _renderColumns + columnIndex, 2, Lines );
   }
}
