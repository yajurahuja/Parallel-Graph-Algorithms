import pandas as pd
from glob import glob
import matplotlib.pyplot as plt
import numpy as np

###### BFS ####################################################################

def bfs():
    bfs_logs = glob("log_bfs_source_index*.txt")
    bfs_df = [pd.read_csv(bfs, delim_whitespace=True, usecols=range(1,7)) 
              for bfs in bfs_logs]
    df = pd.concat(bfs_df, ignore_index=True)
    
    df.rename(columns={'Name': 'SourceVertex', 'SourceVertex': 'ThreadsCount', 
                       'ThreadsCount': 'SeqTime', 'SeqTime': 'ParTime',
                       'ParTime':'SpeedUp', 'SpeedUp':'Status'}, inplace=True)
    
    new_df_bs = df.groupby(['ThreadsCount'],as_index=False).SpeedUp.mean()
    
    return new_df_bs

###### Bellman Ford ###########################################################

def bf():
    bf_logs = glob("log_bf_source_index*.txt")
    bf_df = [pd.read_csv(bfs, delim_whitespace=True, usecols=range(1,7)) 
             for bfs in bf_logs]
    df = pd.concat(bf_df, ignore_index=True)
    
    df.rename(columns={'Name': 'SourceVertex', 'SourceVertex': 'ThreadsCount', 
                       'ThreadsCount': 'SeqTime', 'SeqTime': 'ParTime',
                       'ParTime':'SpeedUp', 'SpeedUp':'Status'}, inplace=True)
    
    new_df_bf = df.groupby(['ThreadsCount'],as_index=False).SpeedUp.mean()
    
    return new_df_bf

###############################################################################

## Plots ######################################################################

def plots(bfs, bf):
    plt.rcParams["figure.dpi"] = 200
    bfs['ThreadsCount'] = np.log2(bfs['ThreadsCount'])
    bfs.plot(x = 'ThreadsCount', y = 'SpeedUp', logx = False,
             marker = "v", 
             title = 'Speedup vs ThreadCount for BFS',
             xlabel = '$log_2$ (Number of Threads)',
             ylabel = 'SpeedUp')
    plt.grid()
    plt.show()
    bf['ThreadsCount'] = np.log2(bf['ThreadsCount'])
    bf.plot(x = 'ThreadsCount', y = 'SpeedUp', logx = False,
             marker = '*',
             c = 'red',
             title = 'Speedup vs ThreadCount for Bellman Ford',
             xlabel = '$log_2$ (Number of Threads)',
             ylabel = 'SpeedUp')
    plt.grid()
    plt.show()
    
    
###############################################################################
    
bfs = bfs()
#print(" BFS Speedup trend with number of threads ")
#print(bfs)
#print()
bf = bf()
#print(" Bellman Ford Speedup trend with number of threads")
#print(bf)

plots(bfs, bf)
