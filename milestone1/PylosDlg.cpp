#include "MyLib.h"
#include "PylosDlg.h"

// static
Class PylosDlg::mClass = Class("PylosDlg", &PylosDlg::Create);

// static
Class *PylosDlg::GetClassPtr()
{
   return &mClass;
}

// static
Object *PylosDlg::Create()
{
   return new PylosDlg();
}

bool PylosDlg::Run(std::istream &in, std::ostream &out, void *data)
{
   char resp;
   PylosBoard::Rules *rules = (PylosBoard::Rules *) data;
   out << "Marble weight: " << rules->GetMarble() << std::endl;
   out << "Level weight: " << rules->GetLevel() << std::endl;
   out << "Free weight: " << rules->GetFree() << std::endl;
   out << "Modify? [y/n] ";

   if ((in >> resp).eof())
      throw BaseException("Unexpected EOF");

   while (in.get() != '\n' && !in.eof())
      ;

   if (resp == 'y') {
      out << std::endl;
      ReadMethodInt(in, out, "Enter marble weight: ", rules,
       &PylosBoard::Rules::SetMarble);
      ReadMethodInt(in, out, "Enter level weight: ", rules,
       &PylosBoard::Rules::SetLevel);
      ReadMethodInt(in, out, "Enter free weight: ", rules,
       &PylosBoard::Rules::SetFree);
   }

   return resp == 'y';
}

void PylosDlg::ReadMethodInt(std::istream &in, std::ostream &out,
 std::string prompt, PylosBoard::Rules *rls, void (PylosBoard::Rules::*x)(int))
{
   int val, ret;
   char extra;
   std::string line;
   while (1) {
      out << prompt;

      do {
         getline(in, line);
         if (in.eof())
            throw BaseException("Unexpected EOF");
      } while (line.empty());

      ret = sscanf(line.c_str(), "%d %c", &val, &extra);

      if (ret == 0) {
         out << "Badly formatted input" << std::endl;
         continue;
      } else if (ret == 2) {
         out << "Unexpected garbage after value." << std::endl;
         continue;
      } else {
         try {
            (rls->*x)(val);
            return;
         } catch (BaseException e) {
            out << "Error: " << e.what() << std::endl;
         }
      }
   }
}
