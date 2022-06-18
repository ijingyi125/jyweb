#pragma once
#include <windows.h>



class CPUusage {
    
    typedef struct __PROCESS_MEMORY_COUNTERS {
        DWORD cb;
        DWORD PageFaultCount;
        SIZE_T PeakWorkingSetSize;
        SIZE_T WorkingSetSize;
        SIZE_T QuotaPeakPagedPoolUsage;
        SIZE_T QuotaPagedPoolUsage;
        SIZE_T QuotaPeakNonPagedPoolUsage;
        SIZE_T QuotaNonPagedPoolUsage;
        SIZE_T PagefileUsage;
        SIZE_T PeakPagefileUsage;
    } _PROCESS_MEMORY_COUNTERS,*_PPROCESS_MEMORY_COUNTERS;


    typedef union _PSAPI_WORKING_SET_BLOCK {
        ULONG_PTR Flags;
        struct {
            ULONG_PTR Protection : 5;
            ULONG_PTR ShareCount : 3;
            ULONG_PTR Shared : 1;
            ULONG_PTR Reserved : 3;
        #if defined(_WIN64)
                ULONG_PTR VirtualPage : 52;
        #else
                ULONG_PTR VirtualPage : 20;
        #endif
        };
    } PSAPI_WORKING_SET_BLOCK, *PPSAPI_WORKING_SET_BLOCK;

    typedef struct _PSAPI_WORKING_SET_INFORMATION {
        ULONG_PTR NumberOfEntries;
        PSAPI_WORKING_SET_BLOCK WorkingSetInfo[1];
    } PSAPI_WORKING_SET_INFORMATION, *PPSAPI_WORKING_SET_INFORMATION;

    typedef struct _PERFORMANCE_INFORMATION {
        DWORD cb;
        SIZE_T CommitTotal;
        SIZE_T CommitLimit;
        SIZE_T CommitPeak;
        SIZE_T PhysicalTotal;
        SIZE_T PhysicalAvailable;
        SIZE_T SystemCache;
        SIZE_T KernelTotal;
        SIZE_T KernelPaged;
        SIZE_T KernelNonpaged;
        SIZE_T PageSize;
        DWORD HandleCount;
        DWORD ProcessCount;
        DWORD ThreadCount;
    } PERFORMANCE_INFORMATION, *PPERFORMANCE_INFORMATION, PERFORMACE_INFORMATION, *PPERFORMACE_INFORMATION;

    typedef void (CALLBACK* GetProcessMemoryInfo)(HANDLE Process, _PPROCESS_MEMORY_COUNTERS ppsmemCounters, DWORD cb);
    typedef BOOL (CALLBACK* QueryWorkingSet)(HANDLE Process, PVOID pv, DWORD cb);
    typedef BOOL (CALLBACK* GetPerformanceInfo)(PPERFORMANCE_INFORMATION pPerformanceInformation, DWORD cb);
private:
    //typedef long long int64_t;
    //typedef unsigned long long uint64_t;
    typedef  INT64 int64_t;
    typedef INT64 uint64_t;
    HANDLE _hProcess;
    int _processor;//cpu����
    int64_t _last_time; //��һ�ε�ʱ��
    int64_t _last_system_time;


    // ʱ��ת��
    uint64_t file_time_2_utc(const FILETIME* ftime)
    {
        LARGE_INTEGER li;

        li.LowPart = ftime->dwLowDateTime;
        li.HighPart = ftime->dwHighDateTime;
        return li.QuadPart;
    }

    // ���CPU�ĺ���
    int get_processor_number()
    {
        SYSTEM_INFO info;
        GetSystemInfo(&info);
        return info.dwNumberOfProcessors;
    }

    //��ʼ��
    void init()
    {
    _last_system_time = 0;
    _last_time = 0;
    _hProcess = 0;
    }

    //�رս��̾��
    void clear()
    {
        if (_hProcess) 
        {
            CloseHandle(_hProcess);
            _hProcess = 0;
        }
    }

public:
    CPUusage(DWORD ProcessID) 
    { 
        init(); 
        _processor = get_processor_number();
        setpid(ProcessID);
    }
    CPUusage(HANDLE hProcess) 
    { 
        init(); 
        _processor = get_processor_number();
        _hProcess = hProcess;
    }
    CPUusage() { init(); _processor = get_processor_number(); }
    ~CPUusage() { clear(); }

    //����ֵΪ���̾��, ���ж�OpenProcess�Ƿ�ɹ�
    HANDLE setpid(DWORD ProcessID) 
    { 
        clear();//���֮ǰ���ӹ���һ������, ���ȹر����ľ��
        init(); 
        return _hProcess= OpenProcess(PROCESS_ALL_ACCESS, false, ProcessID); 
    }

    // -1 ��Ϊʧ�ܻ�������˳��� ����ɹ�, �״ε��û᷵��-2����;��setpid������PID���״ε���Ҳ�᷵��-2��
    double get_cpu_usage()
    {
        FILETIME now;
        FILETIME creation_time;
        FILETIME exit_time;
        FILETIME kernel_time;
        FILETIME user_time;
        int64_t system_time;
        int64_t time;
        int64_t system_time_delta;
        int64_t time_delta;

        DWORD exitcode;

        double cpu = -1;

        if (!_hProcess) return -1;

        GetSystemTimeAsFileTime(&now);

        //�жϽ����Ƿ��Ѿ��˳�
        GetExitCodeProcess(_hProcess, &exitcode);
        if (exitcode != STILL_ACTIVE)
        {
            clear();
            return -1;
        }

        //����ռ��CPU�İٷֱ�
        if (!GetProcessTimes(_hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
        {
            clear();
            return -1;
        }
        system_time = (file_time_2_utc(&kernel_time) + file_time_2_utc(&user_time)) / _processor;
        time = file_time_2_utc(&now);

        //�ж��Ƿ�Ϊ�״μ���
        if ((_last_system_time == 0) || (_last_time == 0))
        {
            _last_system_time = system_time;
            _last_time = time;
            return -2;
        }

        system_time_delta = system_time - _last_system_time;
        time_delta = time - _last_time;

        if (time_delta == 0)
        {
            return -1;
        }

        cpu = (double)system_time_delta * 100 / (double)time_delta;
        _last_system_time = system_time;
        _last_time = time;
        return cpu;
    }
    int get_mem(int& PeakWorkingSetSize)
    {
        static HMODULE hModule = LoadLibrary(TEXT("Kernel32.dll"));
        static GetProcessMemoryInfo fun_GetProcessMemoryInfo = (GetProcessMemoryInfo)GetProcAddress(hModule, "GetProcessMemoryInfo");
        if (!fun_GetProcessMemoryInfo)
        {
            hModule = LoadLibrary(TEXT("Psapi.dll"));
            if (!hModule)throw "��ȡPsapi.dll���ʧ��";
            fun_GetProcessMemoryInfo = (GetProcessMemoryInfo)GetProcAddress(hModule, "GetProcessMemoryInfo");
        }

        if (!fun_GetProcessMemoryInfo)
            return 0;
        _PROCESS_MEMORY_COUNTERS pm = { 0 };
        pm.cb = sizeof(pm);
        fun_GetProcessMemoryInfo(_hProcess, &pm, sizeof(pm));
        PeakWorkingSetSize = pm.PeakWorkingSetSize;
        return pm.WorkingSetSize;
    }
};