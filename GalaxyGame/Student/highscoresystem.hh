#ifndef HIGHSCORESYSTEM_HH
#define HIGHSCORESYSTEM_HH

#include <string>
#include <vector>

#include <QString>

namespace Student
{

/*!
 * \brief HighScore struct includes one players name and score
 *
 */

struct HighScore
{
    std::string player;
    int score;
};

/*!
 * \brief HighScoreSystem class includes operations for highscore
 *        textfiĺe reading/writing and checks if player got to the
 *        leaderboard
 */
class HighScoreSystem
{
public:

    /*!
     * \brief HighScoreSystem class constructor
     */
    HighScoreSystem();

    /*!
     * \brief HighScoreSystem destructor
     */
    ~HighScoreSystem();

    /*!
     * \brief reads highscores.txt file and saves the data into vector of HighScore-structs
     */
    void read();

    /*!
     * \brief (over)writes the data from rankings-vector into highscore.txt file
     */
    void write();

    /*!
     * \brief getList returns current ranking-lsit (vector of HighScore-structs)
     * \return vector
     */
    std::vector<HighScore> getList();

    /*!
     * \brief goesToHighScoreList checks if player who just ended the game gets to the top-10 leaderboard
     * \param currentScore
     * \return true or false
     */
    bool goesToHighScoreList(int currentScore);

    /*!
     * \brief getIndex returns index of rankings-vector where player who just ended the game is going to
     *        be placed
     * \param score
     * \return index of vector
     */
    int getIndex(int score);

    /*!
     * \brief reArrangeList rearranges the rankings-list with new player placed on it
     * \param name players name
     * \param score players score
     */
    void reArrangeList(QString name, unsigned score);

    /*!
     * \brief display test-method for HighScoreSystem class, no real use in final version
     */
    void display();

private:

    /*!
     * \brief filepath_ is the path to the highscore.txt file in working directory
     */
    std::string filepath_;

    /*!
     * \brief leaderBoard_ is the top-10 rankings-list
     */
    std::vector<HighScore> leaderBoard_;
};

#endif // HIGHSCORESYSTEM_HH

}//Student
