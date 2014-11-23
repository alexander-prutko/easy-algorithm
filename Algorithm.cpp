#include <iostream>
#include <iomanip>
//#include <fstream>
#include <vector>
#include <string>
#include "array.h"
#include "list.h"
#include "dllist.h"
#include "sort_algorithm.h"
#include "sort.h"
#include "pod.h"

int main() {
  using namespace std;
  using namespace easy_algorithm;

  vector<DataStructure* (*)()> vpfCreate;                   // Вектор указателей на функции создания структуры данных с определенным типом элементов
  vpfCreate.push_back(DSCreate<PODss, Array>::create);      // Array - массив; List - список; DLList - двусвязный список
  vpfCreate.push_back(DSCreate<PODbs, Array>::create);      // POD (Plain Old Data) - простые структуры с данными (определены только operator <, <<, >>)
  vpfCreate.push_back(DSCreate<PODsb, Array>::create);      // PODxy, где x - размер ключа, y - размер значения
  vpfCreate.push_back(DSCreate<PODbb, Array>::create);      // s - маленький, b - большой
  vpfCreate.push_back(DSCreate<PODss, List>::create);       // каждая функция создает структуру из 1000 элементов
  vpfCreate.push_back(DSCreate<PODbs, List>::create);
  vpfCreate.push_back(DSCreate<PODsb, List>::create);
  vpfCreate.push_back(DSCreate<PODbb, List>::create);
  vpfCreate.push_back(DSCreate<PODss, DLList>::create);
  vpfCreate.push_back(DSCreate<PODbs, DLList>::create);
  vpfCreate.push_back(DSCreate<PODsb, DLList>::create);
  vpfCreate.push_back(DSCreate<PODbb, DLList>::create);

  vector<DataStructure*> vpDS;                              // Вектор указателей на структуры данных
  for (vector<DataStructure* (*)()>::iterator ib = vpfCreate.begin(), ie = vpfCreate.end(); ib != ie; ++ib)
    vpDS.push_back((*ib)());                                // Наполняется с помощью вызова каждой функции создания из вектора vpfCreate

  vector<string> DataStructureName;
  DataStructureName.push_back("Array");
  DataStructureName.push_back("List");
  DataStructureName.push_back("Doubly Linked List");

  vector<string> DataParameters;
  DataParameters.push_back("small keys, small values");
  DataParameters.push_back("big keys, small values");
  DataParameters.push_back("small keys, big values");
  DataParameters.push_back("big keys, big values");

  /*ofstream file("unsort.txt");
  file << *(vpDS[0]);
  file.close();*/

  vector<SortAlgorithm*> vSA;                               // Вектор с указателями на объекты, реализующие сортировку
  vSA.push_back(new SelectionSort);
  vSA.push_back(new InsertionSort);
  vSA.push_back(new BubbleSort);
  vSA.push_back(new ShellSort);
  vSA.push_back(new QuickSort);

  vector<string> SortName;
  SortName.push_back("Selection");
  SortName.push_back("Insertion");
  SortName.push_back("Bubble");
  SortName.push_back("Shell");
  SortName.push_back("Quick");

  vector<pair<int, int> > SortTable;                        // Вектор - таблица. 1-е число - номер структуры данных из вектора vpDS. 2-е - номер сортирующего объекта
  SortTable.push_back(make_pair<int, int>(0, 0));           // Array<PODss> SelectionSort
  SortTable.push_back(make_pair<int, int>(1, 1));           // Array<PODbs> InsertionSort
  SortTable.push_back(make_pair<int, int>(11, 3));          // DLList<PODbb> ShellSort

  vector<SortTime> SortTimeTable;                           // Вектор со статистикой для каждой сортировки из таблицы сортировки SortTable

  // Объект, подсчитывающий время выполнения операций
  TimeObserver* to = new TimeObserver;

  vector<pair<int, int> >::iterator iSortTable = SortTable.begin();
  // Объект-фасад
  Sort s(vpDS[0], vSA[0], to);
  while (iSortTable != SortTable.end()) {
    s.setDataStructure(vpDS[iSortTable->first]);
    s.setSortAlgorithm(vSA[iSortTable->second]);
    s.resetTimeObserver();
    // Выполнение сортировки
    s.sort();
    SortTimeTable.push_back(SortTime(s.getTotalTime(), s.getComparisonTime(), s.getAssignmentTime(), s.getSearchTime()));  // Запись статистики
    ++iSortTable;
  }

  iSortTable = SortTable.begin();
  vector<SortTime>::iterator iSTT = SortTimeTable.begin();
  ios_base::fmtflags ff = cout.flags();
  cout.precision(5);
  cout.setf(ios::scientific | ios::left);
  while (iSTT != SortTimeTable.end()) {                                                               // Вывод статистики
    cout << "Sorting " << DataStructureName[iSortTable->first / 4] \
         << " (" << DataParameters[iSortTable->first % 4] << ") of 1000 elements" << endl \
         << "via " << SortName[iSortTable->second] << " Sort" << endl << endl;
    cout << setw(45) << "Total comparison time (ms): " << iSTT->comp << endl;
    cout << setw(45) << "Total assignment time (ms): " << iSTT->assign << endl;
    cout << setw(45) << "Total search time (ms): " << iSTT->search << endl;
    cout << setw(45) << "Comparison, assignment and search time (ms): " << iSTT->comp + iSTT->assign + iSTT->search << endl;
    cout << setw(45) << "Total time (ms): " << iSTT->total << endl <<endl;
    ++iSTT;
    ++iSortTable;
  }
  cout.flags(ff);

  cout << "Press Enter";
  cin.get();

  for (vector<DataStructure*>::iterator ipDS = vpDS.begin(), ipDSe = vpDS.end(); ipDS != ipDSe;)      // Удаление созданных объектов
  { delete *(ipDS++); }
  for (vector<SortAlgorithm*>::iterator iSA = vSA.begin(), iSAe = vSA.end(); iSA != iSAe;)
  { delete *(iSA++); }
  delete to;

  return 0;
}
