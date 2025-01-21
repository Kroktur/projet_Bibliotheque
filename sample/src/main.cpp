//#include <iostream>
//#include "mediatheque.h"
//int main()
//{
//
//	bibliothecaire m_bibliothequere(new mediatheque);
//	std::string address = "45 sentes des radoubs";
//	m_bibliothequere.CreateClientAccount("Arthur", "Blanchet", 18, "45 sentes des radoubs", "0643506540");
//	m_bibliothequere.CreateClientAccount("Arthur", "Blanchet", 18, "45 sentes des radoubs", "0643506540");
//	m_bibliothequere.CreateClientAccount("zaza", "Blanchet", 18, "45 sentes des radoubs", "0643506540");
//	int age = 19;
//	std::cout << "//////////////////////////////////" << std::endl;
//	m_bibliothequere.showclientbyname("Arthur");
//	std::cout << "//////////////////////////////////" << std::endl;
//	m_bibliothequere.showallclient();
//	std::cout << "//////////////////////////////////" << std::endl;
//	m_bibliothequere.removebyname("Arthur");
//	m_bibliothequere.showallclient();
//	std::cout << "//////////////////////////////////" << std::endl;
//	m_bibliothequere.createBook("lelivredelajungle", "DSDJQZE323");
//	m_bibliothequere.createBook("lelivrepouetpouet", "DSDJQZE323");
//	m_bibliothequere.createBook("lelivrecrapeau", "DSDJQZE323");
//	m_bibliothequere.removeVideoGamebytitle("lelivredelajungle");
//	m_bibliothequere.showallmedia();
//	std::cout << "//////////////////////////////////" << std::endl;
//
//	/*Client* client = new Client("aea", "dzqd",53534,"dzq","dqsd");
//	Media* media = new Book("sqetset","dqsdqd");
//	NodeList list;
//	ClientNode* myclient = new ClientNode(client );
//	MediaNode* nymedia = new MediaNode(media);
//	list.PushBack(myclient);
//	list.PushBack(nymedia);
//	auto clientmodif = static_cast<ClientNode*>(list[0]);
//	std::cout <<list[0]->getObject()->gettype();
//	std::cout << list[1]->getObject()->gettype();
//	if (list[1]->getObject()->gettype() == 1)
//	{
//		auto mediamodif = static_cast<Media*>(list[1]->getObject());
//		auto book = static_cast<Book*> (mediamodif);
//
//	}
//	std::cout << "hello world" << std::endl;
//	return 0;*/
//	return 0;
//}
#include <iostream>
#include "Consoleframebuffer.h"


int main()
{
    ConsoleFramebuffer cfb;
    cfb.setString("zimbaboué");
    cfb.setString("tortue", White, Blue);
    cfb.setString("tortue");
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);

    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);

    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("tortue", Red);
    cfb.setString("wakanda", White, Blue);

    while (true)
    {

        cfb.writeconsol();
        cfb.updatesize();
        cfb.show();
    }
}