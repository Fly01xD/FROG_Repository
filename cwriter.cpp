#include "cwriter.h"
#include "creader.h"
#include <fstream>

CWriter::CWriter(GameData *_data) : MyData(_data)
{
    SaveScore(MyData);
}

void CWriter::SaveScore(GameData *_data)
{
    int Score[3];

    //wczytanie danych z pliku z poprzednimi najlepszymi wynikami
    CReader reader;
    reader.ReadScore(Score);

    int CurrentScore = _data->score;
    bool change = false;

    for (int i = 0; i < 3; i++)
    {
        //Jeśli nasz wynik jest większy od któregoś z najlepszych to go nadpisujemy
        if (CurrentScore > Score[i])
        {
            //Żeby nie stracić innych najlepszych wyników to przechodzimy przez tablice
            // i robimy tak żeby nasze wyniki były ułożone po kolei
            for (int j = 2; j > i; j--)
            {
                Score[j] = Score[j - 1];
            }
            Score[i] = CurrentScore;
            change = true;
            break;
        }
    }

    //Jeśli jakiś wynik się zmieni plik z TopScorami się zmienia
    if (change)
    {
        std::ofstream out("ScoreBoard");
        if (out.is_open())
        {
            for (int i = 0; i < 3; i++) out << Score[i] << " ";
            out.close();
        }
    }
}