#include <QByteArray>
#include <archive.h>
class unzipTool{
 public:
  unzipTool(){};
  ~unzipTool(){close();}
  int getNumEntries();
  const char*getEntryName();
  bool open(QByteArray buf);
  char* entryName(const char*dir,int index);
  void close();
 private:
  QByteArray*data;
  archive *a;
  archive_entry *entry;
 protected:
};