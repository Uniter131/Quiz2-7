#include <bangtal>
using namespace bangtal;

int main()
{
    auto room1 = Scene::create("룸1", "Images/배경-1.png");
    auto room2 = Scene::create("룸2", "Images/배경-2.png");
    auto door1 = Object::create("Images/문-오른쪽-닫힘.png", room1, 800, 270);
    auto door2 = Object::create("Images/문-왼쪽-닫힘.png", room2, 200, 250);
    auto key = Object::create("Images/열쇠.png", room1, 600, 150);
    auto swtch = Object::create("Images/스위치.png", room2, 1200, 500);

    bool closed1 = true;
    bool closed2 = true;
    
    key->setScale(0.2f);
    key->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        object->pick();
        return true;
    });

    door1->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        if (!closed1) {
            room2->enter();
            showMessage("숨겨진 문을 찾아 탈출하세요!");
            door2->hide();
            swtch->setScale(2.7f);
        }
        else if(key->isHanded()) {
            object->setImage("Images/문-오른쪽-열림.png");
            closed1 = false;
        }
        else {
            showMessage("열쇠가 필요합니다.");
        }
        return true;
    });

    door2->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        if (closed2) {
            object->setImage("Images/문-왼쪽-열림.png");
            closed2 = false;
        }
        else {
            endGame();
        }
        return true;
        });

    swtch->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        door2->show();
        return true;
    });

    startGame(room1);
}
