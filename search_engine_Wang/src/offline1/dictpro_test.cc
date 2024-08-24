#include "../../include/offline1/DictProducer.hpp"
#include "../../include/offline2/PageLibPreprocessor.hpp"

using namespace se;
using std::cout;
using std::endl;

//SplitTool *SplitTool::_sptool = nullptr;
int main()
{
    cout << "1" << endl;
    SplitTool *st1 = SplitTool::getInstance();
    cout << "2" << endl;
    se::PageLibPreProcessor pl1(st1);
    cout << "3" << endl;

    pl1.cutRedundantPage("./data/page/newoffset.lib");
    cout << "cutRedundantPage" << endl;

    pl1.readInfoFromFile("./data/page/newpage.lib");
    cout << "readInfoFromFile" << endl;

    se::DictProducer dp1(&pl1, st1);
    cout << "4" << endl;

    dp1.storeDict("./data/offlinedict/dict.txt");
    dp1.storeIndex("./data/offlinedict/dictindex.txt");

    cout << "5" << endl;

    st1->destory();
}