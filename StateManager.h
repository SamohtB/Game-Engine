#pragma once
#include <iostream>

class StateManager
{
public:
    static StateManager* getInstance();
    static void initialize();
    static void destroy();

    enum EditorMode {
        EDITOR = 0,
        PLAY = 1,
        PAUSED = 2
    };

    void setMode(EditorMode mode);
    void startFrameStep();
    void endFrameStep();
    bool insideFrameStep();
    EditorMode getMode();

private:
    StateManager();
    ~StateManager();
    StateManager(StateManager const&) {};
    StateManager& operator=(StateManager const&) {};  

    static StateManager* sharedInstance;

    EditorMode m_editor_mode = EditorMode::EDITOR;
    bool m_frame_stepping = false;
};
