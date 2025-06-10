#pragma once

#include "StdInc.hpp"

#include <utility/Definitions.hpp>


#define MAXIMUM_TASKS_PER_THREAD 64
#define MAXIMUM_THREADS 32

#define PRIORITY_THREAD_LOW 0x0
#define PRIORITY_THREAD_NORMAL 0x1
#define PRIORITY_THREAD_HIGH 0x2
#define PRIORITY_THREAD_CRITICAL 0x3

#define STATUS_THREAD_DESTROYED 0x0
#define STATUS_THREAD_SUSPENDED 0x1
#define STATUS_THREAD_RUNNING 0x2
#define STATUS_THREAD_RUNNING_JOINED 0x4
#define STATUS_THREAD_STARTING (0x1 << 4)
#define STATUS_THREAD_ENDING (0x2 << 4)
#define STATUS_THREAD_WORKING (0x4 << 4)

namespace Ruby {
	using threadinfo_t = unsigned char;
	using taskprocedure_t = void(*)(void*, void*);

	struct TaskData {
		bool lifetime = false;
		void* reserved = nullptr;
		taskprocedure_t procedure = nullptr;
	};

	class Thread {
#ifdef _WIN32
		static unsigned long __stdcall ThreadProc(void* arg);
#endif

	public:
		Thread();
		explicit Thread(threadinfo_t state);
		Thread(threadinfo_t state, threadinfo_t priority);

        static size_t GetLogicalProcessorCount();

		RUBY_NODISCARD const threadinfo_t Priority() const;
        RUBY_NODISCARD const threadinfo_t Priority(threadinfo_t priority);

        RUBY_NODISCARD const threadinfo_t State() const;

		RUBY_NODISCARD const size_t Processed() const;
		RUBY_NODISCARD const size_t Processing() const;

        RUBY_NODISCARD const TaskData* Tasks() const;

        RUBY_NODISCARD bool AddTask(TaskData task);
        RUBY_NODISCARD bool RemoveTask(TaskData task);

        RUBY_NODISCARD bool Suspend();
        RUBY_NODISCARD bool Resume();

		RUBY_NODISCARD bool Wait();
		RUBY_NODISCARD bool Join();

        ~Thread();

	private:
		threadinfo_t m_priority = 0;
		threadinfo_t m_state = 0;

		unsigned long m_id = 0;

		size_t m_processed = 0;
		size_t m_processing = 0;

		void* m_thread = nullptr;
		TaskData* m_tasks = nullptr;

		std::mutex m_guard;
	};

	namespace Threading {
        namespace Globals {
		    inline Thread** threads = nullptr;
        }

		Thread* create(threadinfo_t, threadinfo_t);
		bool create(size_t);

		bool add(TaskData);
		bool remove(TaskData);

		bool destroy(Thread*);
		bool destroy(size_t);
	}
}