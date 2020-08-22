#ifndef CONFIRMAREAWIDGET_H
#define CONFIRMAREAWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class confirmAreaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit confirmAreaWidget(QWidget *parent = nullptr);

    QPushButton *m_pCancelButton;
    QPushButton *m_pConfirmButton;

private:
    void initMemberVariable();
    void initLayout();

private:
    QHBoxLayout *m_pconfirmAreaWidgetHLayout;

signals:

};

#endif // CONFIRMAREAWIDGET_H
