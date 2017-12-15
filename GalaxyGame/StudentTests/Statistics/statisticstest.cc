#include <QString>
#include <QtTest>

#include <stdexcept>
#include <limits>
#include <memory>
#include <iostream>
#include <cmath>

#include "istatistics.hh"
#include "statistics.hh"
#include "gameexception.hh"

class StatisticsTest : public QObject
{
    Q_OBJECT

public:
    StatisticsTest();

private Q_SLOTS:
    void init();
    void testConstructor();

    void testAddSavedShip();
    void testAddLostShip();

    void testAddPoints();
    void testAddManyPoints();
    void testReducePoints();
    void testReduceManyPoints();

    void testAddCredit();
    void testAddManyCredits();
    void testReduceCredits();
    void testReduceManyCreditsNeg();
    void testReduceManyCreditsPos();
    void testExceedLoanCap();

private:
    std::shared_ptr<Common::IStatistics> stats_;
    int startCredit_;
    unsigned goodTestPoints_;
    unsigned badTestPoints_;
    unsigned goodTestCredits_;
    unsigned badTestCredits_;
    int maxLoan_;
};

StatisticsTest::StatisticsTest()
{
    // initialize the test values
    goodTestPoints_ = 1234;
    goodTestCredits_ = 675;

    badTestPoints_ = UINT_MAX;
    badTestCredits_ = UINT_MAX;

    startCredit_ = 123;
    maxLoan_ = 2500;
}

void StatisticsTest::init()
{
    // initialize the Statistic class with every test case.
    stats_.reset();
    stats_ = std::make_shared<Student::Statistics>();
}

void StatisticsTest::testConstructor()
{
    QVERIFY_EXCEPTION_THROWN(stats_->getSavedShips(), Student::StatisticsInvariance);
    QVERIFY_EXCEPTION_THROWN(stats_->getLostShips(), Student::StatisticsInvariance);
    QVERIFY_EXCEPTION_THROWN(stats_->getPoints(), Student::StatisticsInvariance);
    QVERIFY(stats_->getCreditBalance() == 0);
}

void StatisticsTest::testAddSavedShip()
{
    stats_->addSavedShip();
    QCOMPARE(unsigned(1), stats_->getSavedShips());
}

void StatisticsTest::testAddLostShip()
{
    stats_->addLostShip();
    QCOMPARE(unsigned(1), stats_->getLostShips());
}

void StatisticsTest::testAddPoints()
{
    stats_->addPoints(goodTestPoints_);
    QCOMPARE(goodTestPoints_, stats_->getPoints());
}

void StatisticsTest::testAddManyPoints()
{
    // first add legal amount of points
    stats_->addPoints(goodTestPoints_);
    QVERIFY_EXCEPTION_THROWN(stats_->addPoints(badTestPoints_), std::overflow_error);
}

void StatisticsTest::testReducePoints()
{
    stats_->addPoints(goodTestPoints_);
    auto previous = stats_->getPoints();
    stats_->reducePoints(goodTestPoints_ - 1);
    QCOMPARE(previous - (goodTestPoints_ - 1), stats_->getPoints());
}

void StatisticsTest::testReduceManyPoints()
{
    stats_->addPoints(goodTestPoints_);
    QVERIFY_EXCEPTION_THROWN(stats_->reducePoints(badTestPoints_), std::underflow_error);
}

void StatisticsTest::testAddCredit()
{
    auto previous = stats_->getCreditBalance();
    stats_->addCredits(goodTestCredits_);
    QVERIFY(previous + goodTestCredits_ == stats_->getCreditBalance());
}

void StatisticsTest::testAddManyCredits()
{
    //add legal amount first.
    stats_->addCredits(goodTestCredits_);
    QVERIFY_EXCEPTION_THROWN(stats_->addCredits(badTestCredits_), std::overflow_error);
}

void StatisticsTest::testReduceCredits()
{
    auto previous = stats_->getCreditBalance();
    stats_->reduceCredits(goodTestCredits_);
    QVERIFY(previous - goodTestCredits_ == stats_->getCreditBalance());
}

void StatisticsTest::testReduceManyCreditsPos()
{
    QVERIFY_EXCEPTION_THROWN(stats_->reduceCredits(badTestCredits_), std::underflow_error);
}

void StatisticsTest::testReduceManyCreditsNeg()
{
    stats_->reduceCredits(goodTestCredits_);
    QVERIFY_EXCEPTION_THROWN(stats_->reduceCredits(badTestCredits_), std::underflow_error);
}

void StatisticsTest::testExceedLoanCap()
{
    stats_->reducePoints(startCredit_);
    QVERIFY_EXCEPTION_THROWN(stats_->reduceCredits(maxLoan_ * 3), Student::LoanExceeded);
}


QTEST_APPLESS_MAIN(StatisticsTest)

#include "statisticstest.moc"
