**Read this in other languages: [English](README_EN.md), [中文](README.md).**

# Setting up Project GameInstance

1. Navigate to project settings and search for GameInstance.
2. Select it as ReplaySystemInstance.

# GameMode Configuration

1. Replace the spectator player controller class with BP_ReplayPlayerController.

# Recording and Playback

1. Start recording: ReplaySystemInstance->StartRecording
2. Stop recording: ReplaySystemInstance->StopRecording
3. Start playing the replay: ReplaySystemInstance->StartReplay

## Description of BP_ReplayPlayerController Parameters

1. ReplayWidgetObject: Interface for the replay.
2. ExitOpenLevelObject: Level to open when exiting the replay.
