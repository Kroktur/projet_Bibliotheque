#include <iostream>
#include "mediatheque.h"
#include "research.h"
int main()
{
	Database data;
	data.Exe();
	

	/*Client* client = new Client("aea", "dzqd",53534,"dzq","dqsd");
	Media* media = new Book("sqetset","dqsdqd");
	NodeList list;
	ClientNode* myclient = new ClientNode(client );
	MediaNode* nymedia = new MediaNode(media);
	list.PushBack(myclient);
	list.PushBack(nymedia);
	auto clientmodif = static_cast<ClientNode*>(list[0]);
	std::cout <<list[0]->getObject()->gettype();
	std::cout << list[1]->getObject()->gettype();
	if (list[1]->getObject()->gettype() == 1)
	{
		auto mediamodif = static_cast<Media*>(list[1]->getObject());
		auto book = static_cast<Book*> (mediamodif);

	}
	std::cout << "hello world" << std::endl;
	return 0;*/
	return 0;
}
//#include <iostream>
//#include "Consoleframebuffer.h"
//
//
//int main()
//{
//    ConsoleFramebuffer cfb;
//    cfb.setString("zimbaboué");
//    cfb.setString("tortue", White, Blue);
//    cfb.setString("tortue");
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("tortue", Red);
//    cfb.setString("wakanda", White, Blue);
//
//    while (true)
//    {
//
//        cfb.writeConsol();
//        cfb.updateSize();
//        cfb.show();
//    }
//}