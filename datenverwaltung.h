#ifndef DATENVERWALTUNG_H
#define DATENVERWALTUNG_H

#include <QMainWindow>
#include <QDebug>


class Datenverwaltung : public QMainWindow
{
    Q_OBJECT
public:
    explicit Datenverwaltung(QWidget *parent = nullptr);

    void eintragErstellen();       // sind diese methoden nötig?
    void eintragEntfernen();
    void eintragSortieren();
    void eintragEditieren();
    void fehlerHandhabung();

signals:

public slots:

    void eintragSuchen();
    void tabelleAnlegen();
    void tabelleLoeschen();
    void zeileAnlegen();
    void spalteAnlegen();
    void zeileLoeschen();
    void spalteLoeschen();


protected:

private:

};

#endif // DATENVERWALTUNG_H
