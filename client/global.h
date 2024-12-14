#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <functional>
#include <QRegularExpression>
#include "QStyle"
/******************************************************************************
 *
 * @file       global.h
 * @brief      repolish 用来刷新qss
 *
 * @author     infinity
 * @date       2024/12/14
 *****************************************************************************/
extern std::function<void(QWidget*)> repolish;

#endif // GLOBAL_H
