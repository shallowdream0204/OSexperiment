#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
class PCB  // Definition of the process control block class
{
 public:
  int process_number;  // Number of the process
  int arrive_time;     // The arrival time of the process
  int run_time;        // The running time of the process
  int priority_;       // The priority of the process
  int time_slice;      // The time slice of the process
  bool is_arrived;     // Depending on whether the process has arrived or not

 public:
  PCB(int Process_number, int Arrive_time, int Run_time, int Priority_,
      int Time_slice)
      : process_number(Process_number),
        arrive_time(Arrive_time),
        run_time(Run_time),
        priority_(Priority_),
        time_slice(Time_slice),
        is_arrived(false) {}
  PCB(const PCB& p) {
    process_number = p.process_number;
    arrive_time = p.arrive_time;
    run_time = p.run_time;
    priority_ = p.priority_;
    time_slice = p.time_slice;
    is_arrived = p.is_arrived;
  }
  ~PCB() {}
};
class ComparePCBforFCFS {
 public:
  bool operator()(const PCB& p1, const PCB& p2);
};  // The sorting method of the FCFS algorithm
class ComparePCBforSJF {
 public:
  bool operator()(const PCB& p1, const PCB& p2);
};  // The sorting method of the SJF algorithm
class ComparePCBforPriority {
 public:
  bool operator()(const PCB& p1, const PCB& p2);
};  // The sorting method of the Dynamic priority algorithm
void FCFSalgorithm(vector<PCB>& v1);       // algorithm 1
void SJFalgorithm(vector<PCB>& v1);        // algorithm 2
void SRTFalgorithm(vector<PCB>& v1);       // algorithm 3
void Timeslicealgorithm(vector<PCB>& v1);  // algorithm 4
void Priorityalgorithm(vector<PCB>& v1);   // algorithm 5
int main() {
  int algorithmnumber;  // An algorithm that determines the scheduling of a
                        // processor process
  int Process_number, Arrive_time, Run_time, Priority_, Time_slice;
  vector<PCB> v1;  // v1 is a vector to store data of each process
  scanf("%d", &algorithmnumber);
  while (scanf("%d/%d/%d/%d/%d", &Process_number, &Arrive_time, &Run_time,
               &Priority_, &Time_slice) != EOF) {
    PCB p1(Process_number, Arrive_time, Run_time, Priority_, Time_slice);
    v1.push_back(p1);
  }
  switch (algorithmnumber) {
    case (1): {
      FCFSalgorithm(v1);
      break;
    }
    case (2): {
      SJFalgorithm(v1);
      break;
    }
    case (3): {
      SRTFalgorithm(v1);
      break;
    }
    case (4): {
      Timeslicealgorithm(v1);
      break;
    }
    case (5): {
      Priorityalgorithm(v1);
      break;
    }
    default: {
      break;
    }
  }
  return 0;
}
bool ComparePCBforFCFS::operator()(const PCB& p1, const PCB& p2) {
  if (p1.arrive_time == p2.arrive_time) {
    return p1.process_number < p2.process_number;
  } else {
    return p1.arrive_time < p2.arrive_time;
  }
};  // In FCFS algorithm,sorting rules are as follows:
// ascending according to the arrival time, if the arrival time are the same,
// ascending according to the process number
bool ComparePCBforSJF::operator()(const PCB& p1, const PCB& p2) {
  if (p1.run_time == p2.run_time) {
    return p1.arrive_time < p2.arrive_time;
  } else {
    return p1.run_time < p2.run_time;
  }
};  // In SJF algorithm,sorting rules are as follows:
// ascending according to the running time, if the running time are the same,
// ascending according to the arrival time
bool ComparePCBforPriority::operator()(const PCB& p1, const PCB& p2) {
  if (p1.is_arrived == p2.is_arrived && p1.priority_ == p2.priority_ &&
      p1.arrive_time == p2.arrive_time) {
    return p1.process_number < p2.process_number;
  } else if (p1.is_arrived == p2.is_arrived && p1.priority_ == p2.priority_) {
    return p1.arrive_time < p2.arrive_time;
  } else if (p1.is_arrived == p2.is_arrived) {
    return p1.priority_ < p2.priority_;
  } else {
    return p1.is_arrived > p2.is_arrived;
  }
};  // In Dynamic priority algorithm,sorting rules are as follows:
// descending according to the is_arrived, if the is_arrived are the same,
// ascending according to the priority,if the the is_arrived and priority are
// the same, ascending according to the arrival time,if the the
// is_arrived,priority anr the arrival time are the same, ascending according to
// the process number
void FCFSalgorithm(vector<PCB>& v1) {
  int number = 1;                                   // Scheduling sequence
  int time = 0;                                     // Current time
  sort(v1.begin(), v1.end(), ComparePCBforFCFS());  // sort the processes
  for (vector<PCB>::iterator it = v1.begin(); it != v1.end(); it++) {
    if (time < it->arrive_time) {
      time = it->arrive_time;  // There is no process arriving at present,so
                               // change the time
    }
    cout << number << '/' << it->process_number << '/' << time << '/'
         << time + it->run_time << '/' << it->priority_ << endl;
    time += it->run_time; //The time after the end of the current process
    ++number;
  }
};
void SJFalgorithm(vector<PCB>& v1) {
  int time = 0;
  int number = 1;
  bool find = false;  // Determines whether a process has arrived at the
                      // current time in the process queue after sorting
  vector<PCB>::iterator it;
  sort(v1.begin(), v1.end(), ComparePCBforSJF());  // sort by run time
  while (!v1.empty()) {
    for (it = v1.begin(); it != v1.end(); it++) {
      find = false;
      if (it->arrive_time <= time) it->is_arrived = true;
      if (it->is_arrived == true) {
        cout << number << '/' << it->process_number << '/' << time << '/'
             << time + it->run_time << '/' << it->priority_ << endl;
        time += it->run_time;
        ++number;
        v1.erase(it);
        find = true;  // The reached process was found at the current time
        break;
      }
    }
    if (find == false) ++time;
  }
};
void SRTFalgorithm(vector<PCB>& v1) {
  int time = 0;
  int number = 1;
  int count = 0;
  bool first = true;
  bool find = false;
  vector<PCB>::iterator it, it1, it2, it3;
  sort(v1.begin(), v1.end(), ComparePCBforFCFS());
  while (!v1.empty()) {
    find = false;
    for (it = v1.begin(); it != v1.end(); it++) {
      if (it->arrive_time <= time) {
        find = true;
        it->is_arrived = true;
      }
    }
    if (find == false) {
      ++time;
      continue;
    }
    if (first == true) {
      for (it2 = v1.begin(); it2 != v1.end(); it2++) {
        if (it2->is_arrived == true) break;
      }
      for (it1 = v1.begin(); it1 != v1.end(); it1++) {
        if (it1->run_time < it2->run_time && it1->is_arrived == true) it2 = it1;
      }
      it2->run_time = it2->run_time - 1;
      first = false;
      ++time;
      ++count;
      if (it2->run_time == 0) {
        cout << number << '/' << it2->process_number << '/' << time - count
             << '/' << time << it2->priority_ << endl;
        v1.erase(it2);
        count = 0;
        ++number;
        first = true;
      }
    } else {
      for (it3 = v1.begin(); it3 != v1.end(); it3++) {
        if (it3->is_arrived == true) break;
      }
      for (it1 = v1.begin(); it1 != v1.end(); it1++) {
        if (it1->run_time < it3->run_time && it1->is_arrived == true) it3 = it1;
      }
      if (it3 == it2) {
        it2->run_time = it2->run_time - 1;
        ++time;
        ++count;
        if (it2->run_time == 0) {
          cout << number << '/' << it2->process_number << '/' << time - count
               << '/' << time << '/' << it2->priority_ << endl;
          v1.erase(it2);
          first = true;
          count = 0;
          ++number;
        }
      } else {
        cout << number << '/' << it2->process_number << '/' << time - count
             << '/' << time << '/' << it2->priority_ << endl;
        ++time;
        count = 1;
        ++number;
        it3->run_time = it3->run_time - 1;
        if (it3->run_time == 0) {
          cout << number << '/' << it3->process_number << '/' << time - count
               << '/' << time << '/' << it3->priority_ << endl;
          v1.erase(it3);
          first = true;
          count = 0;
          ++number;
        } else {
          it2 = it3;
        }
      }
    }
  }
};
void Timeslicealgorithm(vector<PCB>& v1) {
  int time = 0;
  int number = 1;
  sort(v1.begin(), v1.end(), ComparePCBforFCFS());
  queue<PCB> q1;
  vector<PCB>::iterator it;
  while (q1.empty() != true || v1.empty() != true) {
    if (q1.empty() == true) {
      it = v1.begin();
      time = it->arrive_time;
      q1.push(*it);
      v1.erase(it);
      it = v1.begin();
      while (it != v1.end()) {
        if (it->arrive_time == time) {
          q1.push(*it);
          v1.erase(it);
          it = v1.begin();
        } else {
          break;
        }
      }
    } else {
      if (q1.front().run_time <= q1.front().time_slice) {
        cout << number << '/' << q1.front().process_number << '/' << time << '/'
             << time + q1.front().run_time << '/' << q1.front().priority_
             << endl;
        time += q1.front().run_time;
        ++number;
        q1.pop();
        it = v1.begin();
        while (it != v1.end()) {
          if (it->arrive_time <= time) {
            q1.push(*it);
            v1.erase(it);
            it = v1.begin();
          } else {
            break;
          }
        }
      } else {
        cout << number << '/' << q1.front().process_number << '/' << time << '/'
             << time + q1.front().time_slice << '/' << q1.front().priority_
             << endl;
        time += q1.front().time_slice;
        ++number;
        q1.front().run_time = q1.front().run_time - q1.front().time_slice;
        PCB p1(q1.front());
        q1.pop();
        it = v1.begin();
        while (it != v1.end()) {
          if (it->arrive_time <= time) {
            q1.push(*it);
            v1.erase(it);
            it = v1.begin();
          } else {
            break;
          }
        }
        q1.push(p1);
      }
    }
  }
};
void Priorityalgorithm(vector<PCB>& v1) {
  int time = 0;
  int number = 1;
  bool find;
  vector<PCB>::iterator it;
  while (!v1.empty()) {
    find = false;
    for (it = v1.begin(); it != v1.end(); it++) {
      if (it->arrive_time <= time) {
        it->is_arrived = true;
        find = true;
      }
    }
    if (find == false) {
      ++time;
      continue;
    } else {
      sort(v1.begin(), v1.end(), ComparePCBforPriority());
      it = v1.begin();
      it->priority_ = it->priority_ + 3;
      if (it->run_time <= it->time_slice) {
        cout << number << '/' << it->process_number << '/' << time << '/'
             << time + it->run_time << '/' << it->priority_ << endl;
        time += it->run_time;
        ++number;
        it++;
        while (it != v1.end()) {
          if (it->arrive_time < time && it->priority_ >= 1) {
            it->priority_ = it->priority_ - 1;
          }
          it++;
        }
        it = v1.begin();
        v1.erase(it);
      } else {
        cout << number << '/' << it->process_number << '/' << time << '/'
             << time + it->time_slice << '/' << it->priority_ << endl;
        it->run_time = it->run_time - it->time_slice;
        time += it->time_slice;
        ++number;
        it++;
        while (it != v1.end()) {
          if (it->arrive_time < time && it->priority_ >= 1) {
            it->priority_ = it->priority_ - 1;
          }
          it++;
        }
      }
    }
  }
};