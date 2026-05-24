#include "creader.h"
#include <fstream>

void CReader::ReadScore(int T[3])
{
    std::ifstream in("ScoreBoard");
    if (in.is_open())
    {
        for (int i = 0; i < 3; i++)
        {
            //Jeśli nie da się odczytać danych z pliku to wpisujemy 0,
            //przyda nam się to potem w CWriter
            if (!(in >> T[i]))
            {
                T[i] = 0;
            }
        }
        in.close();
    }
}