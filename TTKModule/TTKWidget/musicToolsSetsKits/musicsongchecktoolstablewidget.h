#ifndef MUSICSONGCHECKTOOLSTABLEWIDGET_H
#define MUSICSONGCHECKTOOLSTABLEWIDGET_H

#include "musicsongchecktoolsunit.h"
#include "musicfillitemtablewidget.h"

/*! @brief The class of the song check tools rename table widget.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_TOOLSET_EXPORT MusicSongCheckToolsRenameTableWidget : public MusicFillItemTableWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicSongCheckToolsRenameTableWidget(QWidget *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Create all items.
     */
    void createAllItems(const MusicSongCheckToolsRenames &items);

public Q_SLOTS:
    /*!
     * Table widget list cell click.
     */
    virtual void listCellClicked(int row, int column) override;
    /*!
     * Select all items.
     */
    void selectedAllItems(bool check);

protected:
    /*!
     * Delete current selected row.
     */
    void deleteCurrentRow();

};



/*! @brief The class of the song check tools duplicate table widget.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_TOOLSET_EXPORT MusicSongCheckToolsDuplicateTableWidget : public MusicFillItemTableWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicSongCheckToolsDuplicateTableWidget(QWidget *parent = 0);

    virtual ~MusicSongCheckToolsDuplicateTableWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Create all items.
     */
    void createAllItems(const MusicSongCheckToolsDuplicates &songs);

Q_SIGNALS:
    /*!
     * Add current selected song to play lists.
     */
    void addSongToPlay(const QStringList &list);

public Q_SLOTS:
    /*!
     * Table widget list cell click.
     */
    virtual void listCellClicked(int row, int column) override;
    /*!
     * Select all items.
     */
    void selectedAllItems(bool check);

protected:
    /*!
     * Add selected music song path to list.
     */
    void musicPlay();
    /*!
     * Delete current selected row.
     */
    void deleteCurrentRow();

};



/*! @brief The class of the song check tools quality table widget.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_TOOLSET_EXPORT MusicSongCheckToolsQualityTableWidget : public MusicFillItemTableWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicSongCheckToolsQualityTableWidget(QWidget *parent = 0);

    virtual ~MusicSongCheckToolsQualityTableWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Create all items.
     */
    void createAllItems(const MusicSongCheckToolsQualitys &songs);

Q_SIGNALS:
    /*!
     * Add current selected song to play lists.
     */
    void addSongToPlay(const QStringList &list);

public Q_SLOTS:
    /*!
     * Table widget list cell click.
     */
    virtual void listCellClicked(int row, int column) override;
    /*!
     * Select all items.
     */
    void selectedAllItems(bool check);

protected:
    /*!
     * Add selected music song path to list.
     */
    void musicPlay();
    /*!
     * Delete current selected row.
     */
    void deleteCurrentRow();

};

#endif // MUSICSONGCHECKTOOLSTABLEWIDGET_H
