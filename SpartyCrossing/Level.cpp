/**
 * \file Level.cpp
 *
 * \author Rohan Singh
 */

#include "pch.h"
#include "Level.h"
#include "Tile.h"
#include "Type.h"
#include "Game.h"
#include "LaneMarker.h"
#include "WanderingWolverine.h"
#include "Boat.h"
#include "Car.h"
#include "Interface.h"
#include "Timer.h"
#include<string>
#include<memory>

using namespace std;
using namespace Gdiplus;
using namespace xmlnode;

/// Hero starts at x pos 480
const int HeroStartingXPos = 480;
/// Hero starts at y pos 928
const int HeroStartingYPos = 928;

void CLevel::Load(const std::wstring& filename, CGame* game)
{
    mGame = game;

    try
    {
        // Open the document to read
        shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

        //
        // Traverse the children of the root
        // node of the XML document in memory!!!!
        //

        for (auto node : root->GetChildren())
        {
            auto item = make_shared<CItem>();

            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"types")
            {
                XmlType(node);
            }
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"background")
            {
                XmlBackground(node);
            }
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"river")
            {
                XmlRiver(node);
            }
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"road")
            {
                XmlRoad(node);
            }
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"hero")
            {
                std::shared_ptr<CType> type = make_shared<CType>();
                std::wstring filename = node->GetAttributeValue(L"image", L"");
                std::wstring filename2 = node->GetAttributeValue(L"hit-image", L"");
                type->AddImage(filename);
                type->AddImage(filename2);

                auto hero = make_shared<CHero>(HeroStartingXPos, HeroStartingYPos, type);
                hero->XmlLoad(node);
                mHero = hero;
            }
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"cargo")
            {
                std::wstring cargoPNG = node->GetAttributeValue(L"image", L"");
                std::wstring carriedPNG = node->GetAttributeValue(L"carried-image", L"");
                std::shared_ptr<CType> type1 = make_shared<CType>();
                std::shared_ptr<CType> type2 = make_shared<CType>();
                type1->AddImage(cargoPNG);
                type2->AddImage(carriedPNG);

                std::wstring cargoID = L"Cargo";
                std::wstring carriedID = L"Carried";

                mTypes[cargoID] = type1;
                mTypes[carriedID] = type2;

                shared_ptr<CCarryObject> cargo = make_shared<CCarryObject>();
                cargo->XmlLoad(node, type1, type2);
                mItems.push_back(cargo);
                mCargo.push_back(cargo);

                float cargoX = float(node->GetAttributeIntValue(L"x", 0)) * 64;
                mCargoPositions.push_back(cargoX);
            }
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"wolverine")
            {
                std::shared_ptr<CType> type = make_shared<CType>();
                std::wstring filename = node->GetAttributeValue(L"image", L"");
                type->AddImage(filename);

                auto wolv = make_shared<CWanderingWolverine>(type);
                wolv->XmlLoad(node);
                mItems.push_back(wolv);
                mWolverine = wolv;
            }

            if (item != nullptr)
            {
             
            }
        }


    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }
}

void CLevel::XmlType(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    for (auto child : node->GetChildren())
    {
        shared_ptr<CItem> item;

        if (child->GetType() == NODE_ELEMENT && child->GetName() == L"decor")
        {
            std::wstring filename = child->GetAttributeValue(L"image", L"");
            std::wstring id = child->GetAttributeValue(L"id", L"");
            std::shared_ptr<CType> type = make_shared<CType>();
            type->AddImage(filename);
            mTypes[id] = type;
        }
        if (child->GetType() == NODE_ELEMENT && child->GetName() == L"car")
        {
            std::wstring filename1 = child->GetAttributeValue(L"image1", L"");
            std::wstring filename2 = child->GetAttributeValue(L"image2", L"");
            std::wstring id = child->GetAttributeValue(L"id", L"");
            std::wstring name = child->GetAttributeValue(L"name", L"");
            std::shared_ptr<CType> type = make_shared<CType>();
            type->SetName(name);
            type->AddImage(filename1);
            type->AddImage(filename2);
            mTypes[id] = type;
        }
        if (child->GetType() == NODE_ELEMENT && child->GetName() == L"boat")
        {
            wstring filename = child->GetAttributeValue(L"image", L"");
            wstring id = child->GetAttributeValue(L"id", L"");
            shared_ptr<CType> type = make_shared<CType>();
            type->AddImage(filename);

            mTypes[id] = type;
        }
        if (item != nullptr)
        {
            item->XmlLoad(child);
            mItems.push_back(item);
        }
    }
}

void CLevel::XmlBackground(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    for (auto child : node->GetChildren())
    {
        shared_ptr<CItem> item;

        if (child->GetType() == NODE_ELEMENT && child->GetName() == L"decor")
        {
            std::wstring id = child->GetAttributeValue(L"id", L"");
            item = make_shared<CTile>(this, mTypes[id]);
        }
        if (child->GetType() == NODE_ELEMENT && child->GetName() == L"rect")
        {
            item = make_shared<CLaneMarker>();
        }
        if (item != nullptr)
        {
            item->XmlLoad(child);
            mItems.push_back(item);
        }
    }
}

void CLevel::XmlRiver(const std::shared_ptr<xmlnode::CXmlNode>& node)
{

    shared_ptr<CLane> lane;
    float laneY = float(node->GetAttributeDoubleValue(L"y", 0)) * 64;
    float laneSpeed = float(node->GetAttributeDoubleValue(L"speed", 0)) * 64;
    float laneWidth = float(node->GetAttributeDoubleValue(L"width", 0)) * 64;

    lane = make_shared<CLane>(laneY, laneSpeed, laneWidth);

    for (auto child : node->GetChildren())
    {
        if (child->GetType() == NODE_ELEMENT && child->GetName() == L"boat")
        {
            wstring id = child->GetAttributeValue(L"id", L"");

            auto boat = make_shared<CBoat>(mTypes[id], lane);

            float xPos = float(child->GetAttributeDoubleValue(L"x", 0)) * 64;
            boat->SetLocation(xPos, laneY);
        
            if (boat != nullptr)
            {;
                lane->AddVehicle(boat);
                mBoats.push_back(boat);
                mItems.push_back(boat);
            }
        }
    }
}

void CLevel::XmlRoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{

    shared_ptr<CLane> lane;
    float laneY = float(node->GetAttributeDoubleValue(L"y", 0)) * 64;
    float laneSpeed = float(node->GetAttributeDoubleValue(L"speed", 0)) * 64;
    float laneWidth = float(node->GetAttributeDoubleValue(L"width", 0)) * 64;

    lane = make_shared<CLane>(laneY, laneSpeed, laneWidth);

    for (auto child : node->GetChildren())
    {
        auto item = make_shared<CItem>();

        if (child->GetType() == NODE_ELEMENT && child->GetName() == L"car")
        {
            wstring id = child->GetAttributeValue(L"id", L"");

            auto car = make_shared<CCar>(mTypes[id], lane);

            float xPos = float(child->GetAttributeDoubleValue(L"x", 0)) * 64;
            car->SetLocation(xPos, laneY);

            float st = float(child->GetAttributeDoubleValue(L"swap-time", 0));
            car->SetSwapTime(st);
        
            if (car != nullptr)
            {
                lane->AddVehicle(car);
                mItems.push_back(car);
            }
        }
    }
}

void CLevel::GetItems(CGame* game) 
{
    for (auto &item : mItems) {
        game->AddItems(item);
    }
    game->AddItems(mHero);

    game->SetHero(mHero);

    for (auto &item : mCargo) {
        game->AddItems(item);
    }
}

void CLevel::Update(double elapsed)
{
    if (mGame->GetRunning()) {
        float xPos = mHero->GetX();
        float yPos = mHero->GetY();

        if (xPos < 0 || xPos > 1024 || yPos < 0 || yPos > 1024)
        {
            mMessage = L"You went out \n of bounds!";
            mWon = false;
            mGame->StopLevel();
        }


        bool onBoat = false;
        shared_ptr<CBoat> curBoat;

        for (auto boat : mBoats) {
            float xPos = mHero->GetX();
            float yPos = mHero->GetY();
            bool isOnBoat = boat->HitTest(xPos, yPos);
            if (isOnBoat) {
                onBoat = true;
                curBoat = boat;
            }
        }

        if (onBoat && !mRiverCheat) {
            mHero->BoatRide(true, curBoat->GetSpeed());
        }
        else
        {
            mHero->BoatRide(false, 0);
        }

        mHero->CarryObject(mCarriedObject);

        for (auto itm : mItems) {
            float xPos = mHero->GetX();
            float yPos = mHero->GetY();
            bool hitItem = itm->HitTest(xPos, yPos);
            if (hitItem) {
                bool endGame = itm->Collision();
                if (endGame && !onBoat) {

                    if (itm->GetId() == L"wolv" && !mWolverineCheat) {
                        mMessage = L"You got GOT by \n the Wolverine!";
                        mWon = false;
                        mHero->HeroDeath();
                        mGame->StopLevel();
                    }
                    else if (itm->GetId() == L"r001" && !mRiverCheat)
                    {
                        mMessage = L"You drowned!";
                        mWon = false;
                        mHero->HeroDeath();
                        mGame->StopLevel();
                    }
                    else if (!mRoadCheat) {
                        wstring name = itm->GetName();
                        mMessage = L"You got ran over \nby " + name;
                        mWon = false;
                        mHero->HeroDeath();
                        mGame->StopLevel();
                    }
                }
            }
        }

        for (auto cargo1 : mCargo)
        {
            float heroY = mHero->GetY();

            float y1 = cargo1->GetY();
            wstring prey = cargo1->GetPrey();

            for (auto cargo2 : mCargo)
            {
                float y2 = cargo2->GetY();
                wstring id = cargo2->GetID();

                if (y1 < 128 && y1 == y2 && prey == id && heroY > 128)
                {
                    wstring name1 = cargo1->GetName();
                    wstring name2 = cargo2->GetName();
                    wstring cod = L"Oh no! The " + name1 + L"\n" + L" ate the " + name2;
                    mMessage = cod;
                    mWon = false;
                    mGame->StopLevel();
                }

                if (y1 > 928 && y1 == y2 && prey == id && heroY < 928)
                {
                    wstring name1 = cargo1->GetName();
                    wstring name2 = cargo2->GetName();
                    wstring cod = L"Oh no! The " + name1 + L"\n" + L" ate the " + name2;
                    mMessage = cod;
                    mWon = false;
                    mGame->StopLevel();
                }
            }
        }


        bool levelComplete = true;

        for (auto cargo : mCargo)
        {
            if (cargo->GetY() != 32) {
                levelComplete = false;
            }
        }

        if (levelComplete)
        {
            mMessage = L"Level Complete!";
            mWon = true;
            mGame->StopLevel();
        }
    }
}

void CLevel::RestartLevel()
{
    mHero->HeroDeath();
    mHero->ResetImage();
    mHero->SetPosition(HeroStartingXPos, HeroStartingYPos);
    mHero->DropItem();

    if (mWolverine != nullptr) {
        mWolverine->ResetPosition();
    }

    int cargoPos = 0;
    for (auto cargo : mCargo)
    {
        float xPos = mCargoPositions[cargoPos];
        cargo->SetLocation(xPos, 960);
        cargo->SetDefaultImage();
        cargoPos++;
    }
    mWon = false;
}

void CLevel::PickUpItem(int x, int y)
{
    if (mHero->GetY() <= 128 || mHero->GetY() >= 928)   ///< Hero must be in one of the safe-zones
    {
        for (auto element : mCargo)
        {
            if (element->HitTest(x, y) == true)
            {
                mHero->PickUpObject(element);
                mCarriedObject = element;
                element->SetCarryImage();
                break;
            }
            bool didhit = element->HitTest(x, y);
            bool test = true;
        }
    }
}

void CLevel::DropItem()
{
    if (mHero->GetY() <= 128)
    {
        mCarriedObject->SetLocation(mCarriedObject->GetInitialX(), 32);    ///< Top Safe-Zone, need to change literals
        mHero->DropItem();
        mCarriedObject->SetDefaultImage();
    }
    if (mHero->GetY() >= 928)
    {
        mCarriedObject->SetLocation(mCarriedObject->GetInitialX(), 960);   ///< Bottom Safe-Zone, need to change literals
        mHero->DropItem();
        mCarriedObject->SetDefaultImage();
    }
}
/*
* Loop through all items in level
* call a hittest on each item
* if sparty hit item 
*   Item::collision -> override in hazard classes
*       returns true if kill or false otherwise
*       if true then call level fail function
*/

void CLevel::DrawInterface(Gdiplus::Graphics* graphics, int level)
{   
    std::vector<std::wstring> cargoNames;
    for (auto cargo : mCargo)
    {
        std::wstring name = cargo->GetName();
        cargoNames.push_back(name);
    }
    mInterface.Draw(graphics, level, cargoNames, mGame);
}

void CLevel::UpdateInterface(double elapsed)
{
    mInterface.Update(elapsed);
}

void CLevel::ResetInterface()
{
    mInterface.Reset();
}

/**
 * Handels end of game display
 */
void CLevel::LevelEnd()
{
    mInterface.LevelEnd( mMessage, mWon);
}


void CLevel::ToggleRoadCheat() {
    if (mRoadCheat) {
        mRoadCheat = false;
    }
    else {
        mRoadCheat = true;
    }
}

void CLevel::ToggleRiverCheat() {
    if (mRiverCheat) {
        mRiverCheat = false;
    }
    else {
        mRiverCheat = true;
    }
}

void CLevel::ToggleWolverineCheat() {
    if (mWolverineCheat) {
        mWolverineCheat = false;
    }
    else {
        mWolverineCheat = true;
    }
}