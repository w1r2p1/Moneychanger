#ifndef MTHOME_HPP
#define MTHOME_HPP

#include "core/WinsockWrapper.h"
#include "core/ExportWrapper.h"

#include <opentxs/client/OTRecordList.hpp>

#include <QPointer>
#include <QWidget>


namespace Ui {
class MTHome;
}

class MTHomeDetail;
class QFrame;

class MTHome : public QWidget
{
    Q_OBJECT

private:
    /** Functions **/

//    void PopulateRecords();  // Calls OTRecordList::Populate(), and then additionally adds records from Bitmessage, etc.

    void RefreshRecords();
    void RefreshUserBar();
//  void setupRecordList();

    bool AddMailToMsgArchive(opentxs::OTRecord& recordmt);
    bool AddFinalReceiptToTradeArchive(opentxs::OTRecord& recordmt);

    QWidget * CreateUserBarWidget();

    /** Overview **/
    bool already_init;
    // ------------------------------------------------
    QPointer<MTHomeDetail>  m_pDetailPane;
    // ------------------------------------------------
    QPointer<QFrame>        m_pHeaderFrame;
    // ------------------------------------------------
    opentxs::OTRecordList   m_list;
    opentxs::OTRecordList & GetRecordlist();
    // ------------------------------------------------
    bool    m_bTurnRefreshBtnRed;
    // ------------------------------------------------
public:
    explicit MTHome(QWidget *parent = 0);
    ~MTHome();

    void dialog();

    void SetRefreshBtnRed();
    void RefreshAll();

    void OnDeletedRecord();

    static QString shortAcctBalance(QString qstr_acct_id,   QString qstr_asset_id=QString(""), bool bWithSymbol=true);
    static QString cashBalance     (QString qstr_notary_id, QString qstr_asset_id, QString qstr_nym_id);
    static int64_t rawCashBalance  (QString qstr_notary_id, QString qstr_asset_id, QString qstr_nym_id);
    static int64_t rawAcctBalance  (QString qstrAcctId);

    static QString FormDisplayLabelForAcctButton(QString qstr_acct_id, QString qstr_display_name);

signals:
    void needToPopulateRecordlist();
    void needToDownloadAccountData();
    void needToRefreshDetails(int nRow, opentxs::OTRecordList & theList);

public slots:
    void onRecordlistPopulated();
    void onBalancesChanged();
    void onSetRefreshBtnRed();
    void onNeedToRefreshUserBar();
    void onNeedToRefreshRecords();
    void onRecordDeleted();

private slots:
    void on_tableWidget_currentCellChanged(int row, int column, int previousRow, int previousColumn);

    void on_refreshButton_clicked();

private:
    Ui::MTHome *ui;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MTHOME_HPP
