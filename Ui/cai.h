#ifndef CAI_H
#define CAI_H
#include <qwidget.h>
class MainWindow;

class CAI : public QWidget
{
    Q_OBJECT
public:
    CAI(MainWindow &window, QWidget *parent = nullptr);
    void startAI();
};

#endif // CAI_H
