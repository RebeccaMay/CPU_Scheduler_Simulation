#include "print_opts.h"
using namespace std;

void Print_opts::print_state_transition(const Event* event, Thread::State before_state, Thread::State after_state) {
    if (verbose){
        cout << "At time " << event -> get_time() << ":" << endl;
        cout << "Thread " << event -> thread -> get_id() << " in process " << event -> thread -> process -> get_pid() << endl;
        cout << "Transitioned from " << Thread::get_state_name(before_state) << " to " << Thread::get_state_name(after_state) << endl;
        cout << endl;
    }
}


void Print_opts::print_dispatch_invoked_message(const Event* event, Thread *thread, std::string message) {
    if (verbose){
        cout << "At time " << event -> get_time() << ":" << endl;
        cout << Event::get_type_name(event->get_type()) << endl;
        cout << "Thread " << thread -> get_id() + 1  << " in process " << thread -> process -> get_pid();      //Fixme
        cout << "[" << Process::get_type_name(thread -> process -> get_type()) << "]" << endl;
        cout << message << endl;
        cout << endl;
    }
}

void Print_opts::print_process_details(Process* process) const {
    if (per_thread){
        cout << "Process " << process -> get_pid() << " [" << Process::get_type_name(process -> get_type()) << "]:" << endl;

        const vector<Thread*> threads = process->getThreads();
        for(int i = 0; i < (int)threads.size(); i++){
            cout << std::left << "\tThread " << threads[i]->get_id() << ": " << "  ARR: " << setw(6) << threads[i]->get_arrival_time()
                 << "CPU: " << setw(6) << threads[i]->get_service_time() << "I/O: " <<  setw(6) << threads[i]->get_io_time()
                 << "TRT: " <<  setw(6) << threads[i]->get_turnaround_time() << "END: " <<  setw(6) << threads[i]->get_end_time()
                 << endl;
        }

        cout << endl;
    }
}

void Print_opts::print_statistics(Sys_statistics stats) const {
    for (int i = 0; i < 4; i++){
        cout << Process::get_type_name( (Process::Type) i) << " THREADS:"
             <<  endl
             << "\t" << "Total count: " << "\t\t" << right << setw(6) << stats.count_threads[i]
             << endl
             << "\t" << "Avg response time:" << "\t" << right << setw(6) << fixed << setprecision(2) << stats.response_time[i]
             << endl
             << "\t" << "Avg turnaround time:" << "\t" << right << setw(6) << fixed << setprecision(2) << stats.tat_time[i]
             << endl
             << endl;
    }

    cout << "Total elapsed time:" << "\t\t" << right << setw(6) << stats.elapsed_time
              << endl
              << "Total service time:" << "\t\t" << right << setw(6) << stats.service_time
              << endl
              <<  "Total I/O time:" << "\t\t\t" << right << setw(6) << stats.io_time
              << endl
              << "Total dispatch time:" << "\t\t" << right << setw(6) << stats.dispatch_time
              << endl
              <<  "Total idle time:" << "\t\t" << right << setw(6) << stats.idle_time
              << endl
              << endl
              << "CPU utilization:" <<  "\t\t" << right << setw(5) << stats.cpu_util << "%"
              << endl
              << "CPU efficiency:" << "\t\t\t" << right << setw(5) << stats.cpu_efficiency<< "%"
              << endl;
}
