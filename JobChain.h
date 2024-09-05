#ifndef __JOB_CHAIN_H__
#define __JOB_CHAIN_H__

#include "JobInfo.h"

class JobChain
{
    private:
        int m_StartJobId;
        const int m_EndJobId;
        long long int m_TotalRunTime;
        int m_NumJobs;
        forward_list<JobData> m_JobChain;

    public:
        JobChain(const JobData & lastJob_):
            m_StartJobId(-1),
            m_EndJobId(lastJob_.getStartJobId()),
            m_TotalRunTime(0),
            m_NumJobs(0)
        {
            AddJobToChain(lastJob_);
        }

        void AddJobToChain(const JobData & job_)
        {
            m_JobChain.emplace_front(job_.getStartJobId(),
                                    job_.getStartJobRunTime(),
                                    job_.getNextJobId());

            m_StartJobId = job_.getStartJobId();
            m_TotalRunTime += job_.getStartJobRunTime();
            m_NumJobs++;
        }

        int GetNumJobs() const
        {
            return m_NumJobs;
        }
        double GetAvgRuntime() const
        {
            double n = m_NumJobs;
            return m_TotalRunTime/n;
        }

        static string timeToString(long long int sec)
        {
            int min = sec/60;
            int hr = min/60;

            stringstream ss;
            ss << setfill('0') << setw(2) << hr << ":"
               << setfill('0') << setw(2) << min << ":"
               << setfill('0') << setw(2) << (sec % 60);

            return ss.str();
        }

        template<typename out_stream>
        friend out_stream & operator << (out_stream &out, const JobChain & jc)
        {
            out<<"StartJob: "<< jc.m_StartJobId << endl
                <<"LastJob: "<< jc.m_EndJobId << endl
                <<"JobChainTime: "<< timeToString(jc.m_TotalRunTime)<<endl
                <<"AvgJobTime: "<< timeToString(jc.GetAvgRuntime()) << endl;

            out<<"Job Chain:";
            auto cItr = jc.m_JobChain.cbegin();
            while(cItr != jc.m_JobChain.cend())
            {
                out << ' '<< *cItr;
                cItr++;
            }
            out << endl;
            return out;
        }
};

#endif
