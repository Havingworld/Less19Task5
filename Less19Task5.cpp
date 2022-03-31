/*
В начале каждого хода игроки вращают волчок, то есть выбирают сектор на столе, который сейчас играет.
Всего таких секторов 13. Сектор выбирается так: с клавиатуры вводится офсет (смещение) относительно
текущего сектора на барабане. Исходя из этого офсета вычисляется новый активный сектор, который и 
будет играть в этом ходе. Если выпавший сектор уже играл, выбирает следующий неигравший за ним. 
В начале всей игры стрелка установлена на первом секторе.

Как только играет какой-то из секторов, с него берётся письмо с вопросом — то есть считывается из
файла данного сектора. Вопрос показывается на экране.

После того как вопрос показан, от игрока ожидается ответ на него. Игрок вводит этот ответ с помощью 
стандартного ввода. То, что он ввёл, сравнивается с ответом, который хранится во втором файле,
ассоциированном с активным сектором. Данный файл должен содержать лишь одно слово-ответ.

Если ответ знатока-игрока был правильным, ему начисляется один балл. Если неверен,
то балл уходит телезрителям.

Игра продолжается до тех пор, пока или игрок, или зрители не наберут шесть баллов. После этого
называется победитель и программа заканчивает работу.

Что оценивается
Игра должна корректно работать от первого хода до последнего. В результате обязательно должен
выявляться победитель.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    int nStartSector = 0,   //start sector in step
        nCountPlayerWon = 0,
        nCountViewerWon = 0;
    vector <int> nSectors = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 }; //array questions

    while(nCountPlayerWon < 6 && nCountViewerWon < 6)
    {
        cout << endl << "----------";
        cout << endl << "Player: " << nCountPlayerWon;
        cout << endl << "Viewer: " << nCountViewerWon;
        cout << endl << "New move, enter step: ";

        int nStep;      //step count

        cin >> nStep;
   
        (nStartSector + nStep > 13) ? (nStartSector = (nStartSector + nStep) % 13) : (nStartSector += nStep); //position calculate
        //if question read
        while (nSectors[nStartSector] == 0)     
        {
            (nStartSector > 13) ? (nStartSector = ++nStartSector % 13) : (++nStartSector);
        }

        //cout << nSectors[nStartSector] << endl;
        
        //open question*.txt
        int nTemp = nSectors[nStartSector];
        string sWayQuestion = "question" + to_string(nSectors[nStartSector]) + ".TXT";
        
        ifstream question(sWayQuestion);
        if (question.is_open())
        {
            // print question
            char c = question.get();
            while (!question.eof())
            {
                cout << c;
                c = question.get();
            }
        }
        else
        {
            // show error message
            cout << "Error opening question file";
        }

        question.close();

        //enter player answer
        cout << endl <<"Enter you answer: ";
        string sPlayerAnswer;
        //getline (cin, sPlayerAnswer);
        cin >> sPlayerAnswer;

        //open answer*.txt
        string sWayAnswer = "answer" + to_string(nSectors[nStartSector]) + ".TXT";

        ifstream answer(sWayAnswer);
        if (answer.is_open())
        {
            vector <char> buffer;
            buffer.push_back(answer.get());
            while (!answer.eof())
            {
                buffer.push_back(answer.get()); 
            }
            //check answer
            bool bAnswerCorrect = true;

            //cout << endl << buffer.size();
            //cout << endl << sPlayerAnswer.size();
            if (buffer.size() != sPlayerAnswer.size()) bAnswerCorrect = false;
            else
            {
                for (int i = 0; i < buffer.size() && i < sPlayerAnswer.size(); i++)
                {
                    if (buffer[i] != sPlayerAnswer[i])
                    {
                        bAnswerCorrect = false;
                        break;
                    }
                }
            }
                        
            //who has won
            (bAnswerCorrect) ? nCountPlayerWon++ : nCountViewerWon++;
            
        }
        else
        {
            //show error message
            cout << "Error opening question file";
        }

        answer.close();
        
        //check question read
        nSectors[nStartSector] = 0; 
    }
    cout << endl << "----------";
    cout << endl << "Player: " << nCountPlayerWon;
    cout << endl << "Viewer: " << nCountViewerWon;
    (nCountPlayerWon > nCountViewerWon) ? (cout << endl << "Player won!") : (cout << endl << "Viewer won!");
}
