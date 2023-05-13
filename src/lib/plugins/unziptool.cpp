#include <ztool.h>
#include <unistd.h>
unzipTool::unzipTool(QByteArray buf)
{
  data = new QByteArray(&buf);
}
bool unzipTool::open()
{
  a = archive_read_new();
  if(!a)return false;
  archive_read_support_filter_all(a);
  archive_read_support_format_zip(a);
  return  archive_read_open_memory(a, buf.data(), static_cast<size_t>buf.size())==ARCHIVE_OK;
}
int unzipTool::getNumEntries() // means files in root. Yes do it by counting amount of /'s
{
  int ctr;
  while(archive_read_next_header(a, &entry) == ARCHIVE_OK)
  {
    int amt = 0;
    char * s = archive_entry_pathname(entry);
    for(int i = 0;s[i]; i++) // same as strlen
    {
     if(s[i]=='/')amt++;
    }
    if(amt<=1)ctr++;
  }
  // archive_seek_data(a,0,SEEK_SET);  // rewind is not implemented
  archive_read_free(a);
  open(); // still better than KArchive
  return ctr;
}
void unzipTool::close()
{
  archive_read_free(a);
  delete data;
}