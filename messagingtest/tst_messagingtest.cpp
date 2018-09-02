#include <QtTest>

// add necessary includes here

class MessagingTest : public QObject
{
    Q_OBJECT

public:
    MessagingTest();
    ~MessagingTest();

private slots:
    void test_case1();

};

MessagingTest::MessagingTest()
{

}

MessagingTest::~MessagingTest()
{

}

void MessagingTest::test_case1()
{

}

QTEST_APPLESS_MAIN(MessagingTest)

#include "tst_messagingtest.moc"
