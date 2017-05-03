#ifndef _THREAD_POOL_TESTS_HPP
#define _THREAD_POOL_TESTS_HPP

#include <QObject>
#include <QtTest>

#include <ThreadPool/ThreadPool.hpp>
#include "Task1.hpp"

#define NB_THREAD 4

using namespace TP;

class ThreadPoolTests : public QObject
{
  Q_OBJECT

  private slots:

    void dynamicAllocation();
    void staticAllocation();
};

#endif