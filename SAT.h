#ifndef SAT_H_INCLUDED
#define SAT_H_INCLUDED
#include "Polygon.h"
#include "math.h"
#include <algorithm>

using namespace std;

/**
*   2D-Collison Detection with Seperating Axis Theorem
**/
bool checkCollision(Polygon A, Polygon B)
{    bool collision = false;

    //Schleife durch alle Punkte von A
    for( unsigned int i=0 ; i < A.points.size(); i++ )
    {

        //Projektionsvektor
        Point Axis;

        if( i == (A.points.size()-1 ) )
        {
            Axis.x = A.points.at( 0 ).x - A.points.at( i ).x;
            Axis.y = A.points.at( 0 ).y - A.points.at( i ).y;
        }
        else
        {
            Axis.x = A.points.at( i+1 ).x - A.points.at( i ).x;
            Axis.y = A.points.at( i+1 ).y - A.points.at( i ).y;
        }

        //Normale von Projektionsachse
        float change = Axis.x;
        Axis.x = Axis.y;
        Axis.y = -change;

        //Normieren von P-Achse
        float betragAxis= sqrt( pow( Axis.x, 2) + pow( Axis.y, 2) );
        Axis.x = Axis.x/betragAxis;
        Axis.y = Axis.y/betragAxis;

    /*-----START DOTPROJECTION POLYGON A--*/

        //Array of Dotproject Polygon A
        vector<float> AProjections;
        AProjections.clear();

        //min and max Projection of Polygon A
        float Amin, Amax;

        //Punktprojektieren auf die P-Achse (Skalarprodukt)
        for( unsigned int t=0 ; t <A.points.size(); t++)
        {
            //Skalarprodukt (Punktprojektion) X-Koordinaten multipliziert und mit Y-Koordinatenprodukt addiert
            AProjections.push_back( (A.points.at(t).x * Axis.x ) + (A.points.at(t).y * Axis.y ) );
        }

        //Finding minimal and maximum
        Amin = *min_element( AProjections.begin(), AProjections.end() );
        Amax = *max_element( AProjections.begin(), AProjections.end() );

    /*----END DOTPROJECTION POLYGON A --*/


    /*----START DOTPROJECTION POLYGON B--*/

        //Array of Dotproject Polygon B
        vector<float> BProjections;
        BProjections.clear();

        //minimale und maximale Länge der B-Projektion
        float Bmin;
        float Bmax;

        //Punktprojektieren auf die P-Achse (Skalarprodukt)
        for( unsigned int s=0 ; s < B.points.size(); s++)
        {
            //Skalarprodukt (Punktprojektion) X-Koordinaten multipliziert und mit Y-Koordinatenprodukt addiert
            BProjections.push_back( (B.points.at(s).x * Axis.x ) + (B.points.at(s).y * Axis.y ) );
        }

        //Finding minimal and maximum
        Bmin = *min_element( BProjections.begin(), BProjections.end() );
        Bmax = *max_element( BProjections.begin(), BProjections.end() );

    /*----END DOTPROJECTION POLYGON B---*/

        //Überlappen sich die Projektionen NICHT? (Falls probleme bei if-abfrage auftreten nachzeichnen!)
        if( Amin > Bmax || Bmin > Amax )
        {
            collision = false;
            break;
        }
        //Wenn letzter Durchlauf ist dann hat Collision stattgefunden
        else if ( i == (A.points.size()-1) )
        {
            collision = true;
            break;
        }
    }
    return collision;
}


#endif // SAT_H_INCLUDED
