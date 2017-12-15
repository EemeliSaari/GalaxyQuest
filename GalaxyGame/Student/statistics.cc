#include <limits>
#include <cmath>

#include "statistics.hh"
#include "stateexception.hh"

//TODO use invariant in right places

const int Student::Statistics::MAX_LOAN_ALLOWED = -2500;

Student::Statistics::Statistics(QObject *parent)
    : savedShips_(0), lostShips_(0), points_(0), credits_(0)
{
}

Student::Statistics::~Statistics()
{
}

void Student::Statistics::addSavedShip()
{
    if (savedShips_ > std::numeric_limits<unsigned>::max() - 1)
    {
        throw std::overflow_error("Overflow, sum too big.");
    }
    else
    {
        ++savedShips_;
        emit updateSavedShips(savedShips_);
    }
}

unsigned Student::Statistics::getSavedShips() const
{
    if(savedShips_ == 0)
        throw StatisticsInvariance();
    else
        return savedShips_;
}

void Student::Statistics::addLostShip()
{
    if (lostShips_ > std::numeric_limits<unsigned>::max() - 1)
    {
        throw std::overflow_error("Overflow, sum too big.");
    }
    else
    {
        ++lostShips_;
        emit updateLostShips(lostShips_);
    }
}

unsigned Student::Statistics::getLostShips() const
{
    if(lostShips_ == 0)
        throw StatisticsInvariance();
    else
        return lostShips_;
}

void Student::Statistics::addPoints(unsigned amount)
{
    if (points_ > std::numeric_limits<uint>::max() - amount)
    {
        throw std::overflow_error("Overflow, sum too big.");
    }
    else
    {
        points_ = points_ + amount;
        emit updatePoints(points_);
    }
}

void Student::Statistics::reducePoints(unsigned amount)
{
    if(points_ > std::numeric_limits<unsigned>::max() - amount)
    {
        throw std::underflow_error("Underflow, difference too big.");
    }
    else
    {
        points_ = points_ - amount;
        emit updatePoints(points_);
    }
}

unsigned Student::Statistics::getPoints() const
{
    if(points_ == 0)
        throw StatisticsInvariance();
    else
        return points_;
}

void Student::Statistics::addCredits(unsigned amount)
{
    if (credits_ > std::numeric_limits<unsigned>::max() - amount)
    {
        throw std::overflow_error("Overflow, sum too big.");
    }
    else
    {
        credits_ = credits_ + amount;
        emit updateCredits(credits_);
    }
}

void Student::Statistics::reduceCredits(unsigned amount)
{
    if(std::numeric_limits<int>::max() < amount)
    {
        throw std::underflow_error("Underflow, no matter what.");
    }
    else if(credits_ < 0 && credits_ > std::numeric_limits<int>::min() + (int)amount)
    {
        throw std::underflow_error("Int min limit exceeded.");
    }
    else if(credits_ > 0 && credits_ < std::numeric_limits<int>::min() + (int)amount)
    {
        throw std::underflow_error("Int min limit exceeded.");
    }
    else if(credits_ < 0 && credits_ > MAX_LOAN_ALLOWED + (int)amount)
    {
        throw LoanExceeded();
    }
    else if(credits_ >= 0 && credits_ < MAX_LOAN_ALLOWED + (int)amount)
    {
        throw LoanExceeded();
    }
    else
    {
        credits_ = credits_ - amount;
        emit updateCredits(credits_);
    }
}

int Student::Statistics:: getCreditBalance() const
{
    return credits_;
}
