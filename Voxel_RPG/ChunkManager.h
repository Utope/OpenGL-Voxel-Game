#pragma once
#include <vector>
#include <queue>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "ChunkTask.h"

class ChunkManager {

	/*NOTE: The hashMap used in this class will only be changed on loadingRadius size change
	each chunks "Position" is only relative to the loading Radius
	*/

	/* TODO
		Chunk neigbors need to be updated 
		Probably should put ChunkThreading in a separate class
		Update class needs to be done
		multiple Dynamic casting can be replaced by one dynamic cast and static "checks", which is much quicker
		Many tasks don't actually implement everything they need to
			-Deletion, very basic
			-MeshingTask, needs greedy, possibly multiple types, and possibly add a "basic meshing"
			-Loading, libnoise Generation
		Decide on how RenderMethod should look
		Also getting/setting individual voxels
		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		CHUNKS NEED TO BE EMPTY INITIALIZED TO TEST FOR "NONLOADEDNESS"
		Way to handle chunk state needs to be better
		Should fix this first!

	*/

public:
	ChunkManager(int loadingRadius, int threadCount);
	~ChunkManager();

	void update(glm::vec3 loadingPosition);
	void render();
	
	void setLoadingRadius(int loadingRadius);
	int getLoadingRadius();

	inline Chunk* getChunk(glm::ivec3 positionkey) { return m_loadedChunks.find(positionkey)->second; };

private:
	
	std::unordered_map<glm::ivec3, Chunk*> m_loadedChunks;

	//MultiThreading
	std::vector<std::thread*> m_workerThreads;
	std::atomic<bool> m_threadPoolRunning;
	
	//Cond variable for waiting on queued mutex
	std::condition_variable m_conditionalVar;

	//Queued mutex for getting and adding tasks
	std::mutex m_queuedTaskMutex;

	//Mutex for handling processed tasks
	std::mutex m_processedTaskMutex;

	/*MultiThreading_Variable
		called in 
		_ThreadHandlerFunction
		_AddTaskToLowQ
	*/
	std::queue<ChunkTasks::ChunkTask*> m_lowQ; 
	
	/*MultiThreading_Variable
		called in
		_ThreadHandlerFunction
		_AddTaskToHighQ
	*/
	std::queue<ChunkTasks::ChunkTask*> m_highQ;

	/*MultiThreading_Variable
		called in
		_ThreadHandlerFunction
		_HandleProccessedTasks
	*/
	std::queue<ChunkTasks::ChunkTask*> m_processedTasks;
	//This handles each individual thread
	void _threadHandlerFunction();

	//These are for the main function threading
	//Creates a std::vector of tasks. Size based on numProcessedTasksHandledPerFrame
	void _handleProccessedTasks();
	
	//Handles each individual task.
	//DELETES AND CLEANS UP TASK POINTERS HERE
	//MAKE EDITS IN THIS CLASS WHEN ADDING MORE CHUNKTASKS
	void _handleVectorOfProcessedTasks(std::vector<ChunkTasks::ChunkTask*>);
	
	//Adds a task to the lowQ or highQ respectivly
	//Should be called with "new ...Type of chunkTask"
	void _addTaskToHighQ(ChunkTasks::ChunkTask*);
	void _addTaskToLowQ(ChunkTasks::ChunkTask*);

	//Manager Settings

	//Number of proccessedTask we handle each frame
	//Setting it a 0 means we handle ALL tasks
	int m_numProceesedTasksHandledPerFrame;
	
	//Distance to load chunks from Update positions
	int m_loadingRadius;

};