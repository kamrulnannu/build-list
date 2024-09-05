#ifndef __JOB_INFO_H__
#define __JOB_INFO_H__

#include <bits/stdc++.h>

using namespace std;

class JobData
{
    private:
        int m_JobId;
        int  m_JobRunTime;
        int m_NextJobId;

    public:
        JobData() = default;

        JobData(int startJobId, int runTime, int nextJobId):
            m_JobId(startJobId),
            m_JobRunTime(runTime),
            m_NextJobId(nextJobId)
        {}

        bool isValid() const
        {
            return isValid(m_JobId, m_JobRunTime, m_NextJobId);
        }

        static bool isValid(int jId, int time, int nxtId)
        {
            return ((jId > 0) && (time > 0) && (nxtId >= 0));
        }

        void setStartJobId(int id)
        {
            m_JobId = id;
        }

        void setStartJobRunTime(int time)
        {
            m_JobRunTime =  time;
        }

        void setNextJobId(int id)
        {
            m_NextJobId = id;
        }

        int getStartJobId() const
        {
            return m_JobId;
        }

        int getStartJobRunTime() const
        {
            return m_JobRunTime;
        }

        int getNextJobId() const
        {
            return m_NextJobId;
        }

        bool isLastJob() const
        {
            return (m_NextJobId == 0);
        }

        friend istream& operator>>(istream& is, JobData& j)
        {
            string line;
            if (getline(is, line)) // Read whole line
            {
                //cout<<"LINE: "<<line<<endl;
                stringstream ss(line);
                char delimiter1, delimiter2;

                // Extract fields separated by commas
                if ((ss >> j.m_JobId
                        >> delimiter1
                        >> j.m_JobRunTime
                        >> delimiter2
                        >> j.m_NextJobId) &&
                    delimiter1 == ',' && delimiter2 == ',')
                {
                    if (!j.isValid())
                    {
                        cout<<"ERR: isValid failed, line: "<<line<<endl;
                        is.setstate(ios::failbit);
                    }
                    return is;
                }
                else
                {
                    cout<<"ERR: Invalid input line: "<<line<<endl;
                    is.setstate(ios::failbit); // Set failbit if parsing fails
                }
            }
            return is;
        }
        friend ostream& operator<<(ostream& out, JobData const& j)
        {
            out<<"("<< j.m_JobId<<","<<j.m_JobRunTime<<","<<j.m_NextJobId<<")";
            return out;
        }
};

#endif
