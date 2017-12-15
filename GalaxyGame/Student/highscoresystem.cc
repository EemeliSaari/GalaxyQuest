#include <iostream>
#include <fstream>
#include <sstream>

#include "highscoresystem.hh"

namespace Student
{

HighScoreSystem::HighScoreSystem()
    : filepath_(), leaderBoard_()
{
    filepath_ = "Student/highscores.txt";  // need to set right workspace from QTCreator: Projects -> Run -> Workspace
    read();
}

HighScoreSystem::~HighScoreSystem()
{
}

void HighScoreSystem::read()
{   
    std::ifstream file(filepath_);
    std::string line;

    while (file && getline(file, line)){
        if (line.length() != 0)
        {
            std::string bufferString;
            std::stringstream stringStream(line);
            std::vector<std::string> items;

            while (stringStream >> bufferString)
            {
                items.push_back(bufferString);
            }

            std::string playerName = items[0];
            int score = stoi(items[1]);
            HighScore hsItem;
            hsItem.player = playerName;
            hsItem.score = score;
            leaderBoard_.push_back(hsItem);
        }
        else
        {
            std::cout << "doesn't work" << std::endl;
        }
    }
    file.close();

}

std::vector<HighScore> HighScoreSystem::getList()
{
    return leaderBoard_;
}

void HighScoreSystem::write()
{
    std::ofstream file(filepath_);
    for(auto it = leaderBoard_.begin(); it != leaderBoard_.end(); ++it)
    {
        file << (*it).player << " " << (*it).score << "\n";
    }
    file.close();
}

bool HighScoreSystem::goesToHighScoreList(int currentScore)
{
    if (currentScore > leaderBoard_.at(9).score)
    {
        return true;
    }
    return false;
}

int HighScoreSystem::getIndex(int score)
{
    int index = 0;
    for(auto it = leaderBoard_.begin(); it != leaderBoard_.end(); ++it)
    {
        if(score > (*it).score)
        {
            return index;
        }
        index += 1;
    }
    return index;
}

void HighScoreSystem::reArrangeList(QString name, unsigned score)
{
    int index = getIndex(score);
    HighScore newHs;
    std::string playername = name.toStdString();
    newHs.player = playername;
    newHs.score = score;
    leaderBoard_.insert(leaderBoard_.begin() + index, newHs);
    leaderBoard_.pop_back();
    write();
}

void HighScoreSystem::display()
{
    for(auto it = leaderBoard_.begin(); it != leaderBoard_.end(); ++it)
    {
        std::cout << (*it).player << " : " << (*it).score << std::endl;
    }
}

}//Student
