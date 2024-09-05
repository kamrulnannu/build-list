#include "JobChain.h"


int main()
{
    /*
     * List of all jobs whose nextJobId != 0
     */
    vector<JobData> m_Jobs;

    /*
     * List of all jobs whose nextJobId == 0
     *
     * Number of Chains == m_Last.size();
     */
    vector<JobData> m_LastJobs;

    /*
     * Key: JobData::m_NextJobId
     * Value: Job index at m_Jobs
     */
    unordered_map<int, int> m_NxtJodId2JobIdx;

    /*
     * Job Id of all Jobs. It is used to identify problem with the input
     * file. When a job is added to a chain, the corresponding job id
     * will be removed from this list. It also help to identify duplicate
     * job entries in the input file.
     * At the end of processing all job chains, this set should be empty
     * unless there is problem in the input file.
     */
    unordered_set<int> m_JobIds;

    /*
     * List of all Job Chains
     */
    vector<JobChain> m_JobChains;

    // Skip Header
    string hdr;
    getline(std::cin, hdr);
    //cout<<"HDR:"<<hdr<<endl;

    istream_iterator<JobData> begin(std::cin);
    istream_iterator<JobData> end;

    if (cin.fail() && !cin.eof())
    {
        cout << "Err_0: Malformed Input" << endl;
        return -1;
    }
    while(begin != end)
    {
        auto &jd = *begin;
#if 0
        cout<<"JD: "<<jd<<endl;

        if (cin.fail())
        {
            cout<<"cin.fail() at job line: "<<jd<<endl;
            cout<<"NumJobs: Last:"<<m_LastJobs.size()<<", Others: "<<m_Jobs.size()<<endl;
            cout<<"----Other JObs:\n";
            for (auto &j : m_Jobs)
                cout<<j<<endl;
            cout<<"----Last jobs:\n";
            for (auto &j: m_LastJobs)
                cout<<j<<endl;
            break;
        }
#endif
        if (jd.isLastJob())
            m_LastJobs.push_back(jd);
        else
        {
            m_Jobs.push_back(jd);
            m_NxtJodId2JobIdx[jd.getNextJobId()] = m_Jobs.size()-1;
        }
        if (m_JobIds.count(jd.getStartJobId()) == 0)
            m_JobIds.insert(jd.getStartJobId());
        else
        {
            cerr<<"Err: Duplicate start jod id: "<<jd.getStartJobId()<<", Exiting ...\n";
            return -1;
        }
        begin++;
    }
    // if we failed to parse the input print error and return a error code
    if (cin.fail() && !cin.eof())
    {
        cout << "Err_1: Malformed Input" << endl;
        return -1;
    }

    // Create Chain(s)
    for (auto & last : m_LastJobs)
    {
        JobChain jc(last);
        int startJobId = last.getStartJobId();
        m_JobIds.erase(startJobId);

        while(m_NxtJodId2JobIdx.count(startJobId))
        {
            auto itr = m_NxtJodId2JobIdx.find(startJobId);
            int idx = itr->second;
            const JobData &jd = m_Jobs[idx];
            jc.AddJobToChain(jd);
            startJobId = jd.getStartJobId();
            m_JobIds.erase(startJobId);
        }

        /* one job chain is created */
        m_JobChains.push_back(jc);
    }
    /*
     * All job chain(s) are created
     */

    /*
     * Check if any start job is not a part of any chain. This will
     * happen when error in input file
     */
    if (m_JobIds.size())
    {
        auto itr = m_JobIds.begin();
        cerr<<"Error in input file, following start job(s) are not part of any job chain:";
        while (itr != m_JobIds.end())
        {
            cerr<<' '<<*itr;
            itr++;
        }
        cerr<<'\n';

        //return -1;
    }

    // output the JobChain Info
    cout << "===" << endl;
    ostream_iterator<JobChain> out(cout, "===\n");
    copy(m_JobChains.begin(), m_JobChains.end(), out);

    return 0;
}
