//
//  Game.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Game.h"

#include "Core/Components/StaticMeshComponent.h"
#include "Core/GameObject.h"
#include "Core/World.h"

#include "Renderer/MaterialInstance.h"
#include "Renderer/Renderer.h"
#include "Renderer/RendererFactory.h"
#include "Renderer/StaticMesh.h"
#include "Renderer/Surface.h"
#include "Renderer/Vertex.h"

#include "Util/UniqueArray.h"
#include "Util/Timer.h"

#include "GameInterface.h"
#include "KeyboardHandler.h"
#include "SystemHandler.h"
#include "SystemInfo.h"

Game::Game() : mFirstFrame(true), mLastFrameTime(0), mWorld(nullptr) {

}

Game::~Game() {
}

UniquePtr<World> Game::createWorld() const {
    World* world = new World();
    GameObject* obj = new GameObject();
    
    StaticMeshComponent* smc = new StaticMeshComponent();
    StaticMesh* mesh = new StaticMesh();
    static Vertex vertices[] = {
        { Vector(0, 0, 0), {0, 0, 1}, {0, 0} },
        { Vector(5, 0, 0), {0, 0, 1}, {0, 0} },
        { Vector(5, 5, 0), {0, 0, 1}, {0, 0} }
    };
    
    Surface* surface = new Surface(UniqueArray<Vertex>(vertices), sizeof(vertices) / sizeof(*vertices));
    mesh->addSurface(SharedPtr<Surface>(surface), mRenderer->createMaterial("simple"));
    
    MaterialInstance* material = mesh->getMaterial(surface);
    float color[] = {1.f, 1.f, 0.f, 1.f};
    material->setParameter("uColor", color, sizeof(color));
    
    smc->setMesh(mesh);
    obj->addComponent(smc);
    world->addObject(obj);
    
    return UniquePtr<World>(world);
}

void Game::doFrame() {
    if(!mWorld) {
        setWorld(createWorld());
    }
    
    mMessageQueue.processMessages();
    
#ifndef DEBUG
    float frameTime = Timer::elapsedTime() - mLastFrameTime;
#else
    float frameTime = 1./60.f;
#endif
    if(mFirstFrame) {
        mFirstFrame = false;
        frameTime = 0;
    }
    
    mWorld->update(mGameClock.tickTime(frameTime));
    mWorld->prepareRender(mRenderer.get());
    mRenderer->renderFrame();
    
    mLastFrameTime = frameTime;
}

bool Game::initializeGame() {
    SystemInfo system;
    if(system.hasOpengGL()) {
        mRenderer = RendererFactory::createRenderer(RendererFactory::RENDERER_OPENGL);
        mRenderer->init();
    }
    
    mGameInterface.reset(new GameInterface(&mMessageQueue));
    
    SharedPtr<SystemHandler> systemHandler(new SystemHandler(mRenderer.get()));
    mMessageQueue.registerHandler(systemHandler, MESSAGE_CATEGORY_SYSTEM);
    
    SharedPtr<KeyboardHandler> keyboardHandler(new KeyboardHandler());
    mMessageQueue.registerHandler(keyboardHandler, MESSAGE_CATEGORY_KEYBOARD);
    
    return true;
}

void Game::setWorld(UniquePtr<World> world) {
    mWorld = world;
    mFirstFrame = true;
}

GameInterface* Game::gameInterface() {
    return mGameInterface.get();
}