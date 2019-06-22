/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    NET_CONFIG.H
 *      Purpose: Common TCPnet Definitions
 *      Rev.:    V4.73
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2014 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#ifndef __NET_CONFIG_H__
#define __NET_CONFIG_H__

#include <RTL.h>

/* Definitions */
#define ETH_ADRLEN      6         /* Ethernet Address Length in bytes        */
#define IP_ADRLEN       4         /* IP Address Length in bytes              */
#define OS_HEADER_LEN   4         /* TCPnet 'os_frame' header size           */
                                  /* Frame Header length common for all      */
#define PHY_HEADER_LEN  (2*ETH_ADRLEN + 2) /* network interfaces.            */
#define ETH_MTU         1514      /* Ethernet Frame Max Transfer Unit        */
#define PPP_PROT_IP     0x0021    /* PPP Protocol type: IP                   */
#define TCP_DEF_WINSIZE 4380      /* TCP default window size                 */
#define PASSW_SZ        20        /* Authentication Password Buffer size     */

/* Network Interfaces */
#define NETIF_ETH       0         /* Network interface: Ethernet             */
#define NETIF_PPP       1         /* Network interface: PPP                  */
#define NETIF_SLIP      2         /* Network interface: Slip                 */
#define NETIF_LOCAL     3         /* Network interface: Localhost (loopback) */
#define NETIF_NULL      4         /* Network interface: Null (none)          */

/* Telnet Definitions */
#define TNET_LBUFSZ     96        /* Command Line buffer size (bytes)        */
#define TNET_HISTSZ     128       /* Command History buffer size (bytes)     */
#define TNET_FIFOSZ     128       /* Input character Fifo buffer (bytes)     */

/* SNMP-MIB Definitions */
#define MIB_INTEGER     0x02      /* MIB entry type INTEGER                  */
#define MIB_OCTET_STR   0x04      /* MIB entry type OCTET_STRING             */
#define MIB_OBJECT_ID   0x06      /* MIB entry type OBJECT_IDENTIFIER        */
#define MIB_IP_ADDR     0x40      /* MIB entry type IP ADDRESS (U8[4])       */
#define MIB_COUNTER     0x41      /* MIB entry type COUNTER (U32)            */
#define MIB_GAUGE       0x42      /* MIB entry type GAUGE (U32)              */
#define MIB_TIME_TICKS  0x43      /* MIB entry type TIME_TICKS               */
#define MIB_ATR_RO      0x80      /* MIB entry attribute READ_ONLY           */
#define MIB_OIDSZ       17        /* Max.size of Object ID value             */
#define MIB_STRSZ       110       /* Max.size of Octet String variable       */
#define MIB_READ        0         /* MIB entry Read access                   */
#define MIB_WRITE       1         /* MIB entry Write access                  */

/* SNMP-MIB Macros */
#define MIB_STR(s)      sizeof(s)-1, s
#define MIB_INT(o)      sizeof(o), (void *)&o
#define MIB_IP(ip)      4, (void *)&ip 
#define OID0(f,s)       (f*40 + s) 

/* Debug Module Definitions */
#define MODULE_MEM      0         /* Dynamic Memory Module ID                */
#define MODULE_ETH      1         /* Ethernet Module ID                      */
#define MODULE_PPP      2         /* PPP Module ID                           */
#define MODULE_SLIP     3         /* SLIP Module ID                          */
#define MODULE_ARP      4         /* ARP Module ID                           */
#define MODULE_IP       5         /* IP Module ID                            */
#define MODULE_ICMP     6         /* ICMP Module ID                          */
#define MODULE_IGMP     7         /* IGMP Module ID                          */
#define MODULE_UDP      8         /* UDP Module ID                           */
#define MODULE_TCP      9         /* TCP Module ID                           */
#define MODULE_NBNS     10        /* NBNS Module ID                          */
#define MODULE_DHCP     11        /* DHCP Module ID                          */
#define MODULE_DNS      12        /* DNS Module ID                           */
#define MODULE_SNMP     13        /* SNMP Module ID                          */
#define MODULE_BSD      14        /* BSD Socket Module ID                    */
#define MODULE_HTTP     15        /* HTTP Server Module ID                   */
#define MODULE_FTP      16        /* FTP Server Module ID                    */
#define MODULE_FTPC     17        /* FTP Client Module ID                    */
#define MODULE_TNET     18        /* Telnet Server Module ID                 */
#define MODULE_TFTP     19        /* TFTP Server Module ID                   */
#define MODULE_TFTPC    20        /* TFTP Client Module ID                   */
#define MODULE_SMTP     21        /* SMTP Client Module ID                   */
#define MODULE_SNTP     22        /* SNTP Client Module ID                   */

/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"  {
#endif

typedef struct os_frame {         /* << System frame buffer structure >>     */
  U16 length;                     /* Total Length of data in frame           */
  U16 index;                      /* Buffer Position Index                   */
  U8  data[1];                    /* Buffer data (protocol headers + data)   */
} OS_FRAME;

typedef struct arp_info {         /* << ARP Cache Entry info >>              */
  U8  State;                      /* ARP Cache entry current state           */
  U8  Type;                       /* Cache Entry type                        */
  U8  Retries;                    /* Number of Retries left                  */
  U8  Tout;                       /* Cache Entry Timeout                     */
  U8  HwAdr[ETH_ADRLEN];          /* Ethernet Hardware Address               */
  U8  IpAdr[IP_ADRLEN];           /* Ethernet IP Address                     */
} ARP_INFO;

typedef struct igmp_info {        /* << IGMP Group info >>                   */
  U8  State;                      /* Group membership current state          */
  U8  Tout;                       /* Timeout Timer for sending reports       */
  U8  Flags;                      /* State machine flags                     */
  U8  GrpIpAdr[IP_ADRLEN];        /* Group IP address                        */
} IGMP_INFO;

typedef struct udp_info {         /* << UDP Socket info >>                   */
  U8  State;                      /* UDP Socket entry current state          */
  U8  Opt;                        /* UDP Socket Options                      */
  U8  Flags;                      /* State machine flags                     */
  U8  Tos;                        /* UDP Type of Service                     */
  U16 LocPort;                    /* Local UDP port of Socket                */
  U8  McastTtl;                   /* MultiCast Time To Live                  */
                                  /* Application Event CallBack function     */
  U16 (*cb_func)(U8 socket, U8 *rem_ip, U16 port, U8 *buf, U16 len);
} UDP_INFO;

typedef struct tcp_info {         /* << TCP Socket info >>                   */
  U8  State;                      /* Socket entry current state              */
  U8  Type;                       /* Socket type                             */
  U8  Flags;                      /* State machine flags                     */
  U8  Tos;                        /* Type of service allocated               */
  U8  RemIpAdr[IP_ADRLEN];        /* Remote IP address                       */
  U16 RemPort;                    /* Remote TCP port                         */
  U16 LocPort;                    /* Local TCP port                          */
  U16 MaxSegSize;                 /* Transmit Max. Segment Size              */
  U16 Tout;                       /* Socket idle timeout (in seconds)        */
  U16 AliveTimer;                 /* Keep Alive timer                        */
  U16 RetryTimer;                 /* Retransmission timer                    */
  U8  AckTimer;                   /* Receive Delay-ack timer                 */
  U8  Id;                         /* Socket identification number            */
  U8  Retries;                    /* Number of retries left before aborting  */
  U8  DupAcks;                    /* Number of duplicate acks (fast recovery)*/
  U32 SendUna;                    /* Send Sequence Number unacknowledged     */
  U32 SendNext;                   /* Next Send Sequence Number               */
  U32 SendChk;                    /* Check Sequence Number for dupacks       */
  U32 SendWl1;                    /* Sequence Number of last Window update   */
  U32 SendWl2;                    /* Acknowledge Number of last Window update*/
  U16 SendWin;                    /* Current Send Window                     */
  S16 RttSa;                      /* Scaled Average for RTT estimator        */
  S16 RttSv;                      /* Scaled deViation for RTT estimator      */
  U16 CWnd;                       /* Congestion Window                       */
  U16 SsThresh;                   /* Slow Start Treshold                     */
  U16 RecWin;                     /* Current Receive Window                  */
  U32 RecNext;                    /* Next Receive Sequence Number            */
  OS_FRAME *unack_list;           /* Unacked queue list                      */
                                  /* Application Event-CallBack function     */
  U16 (*cb_func)(U8 socket, U8 event, U8 *p1, U16 p2);
} TCP_INFO;

typedef struct bsd_info {         /* << BSD Socket info >>                   */
  U8  State;                      /* BSD Socket current state                */
  U8  Socket;                     /* Binded TCP/UDP Socket                   */
  U8  Flags;                      /* Flags for Socket Option                 */
  U8  Type;                       /* Type of Socket (SOCK_DGRAM/SOCK_STREAM) */
  U16 LocPort;                    /* Bind local Port                         */
  U16 RemPort;                    /* Remote TCP/UDP Port                     */
  U32 LocIP;                      /* Bind local IP address (net byte order)  */
  U32 RemIP;                      /* Remote IP address     (net byte order)  */
  U8  AcceptSock;                 /* Accept Socket list                      */
  U8  ParentSock;                 /* Parent (server) socket                  */
  U8  Event;                      /* Wait Event flags in RTX environment     */
  U8  Task;                       /* Socket Owner Task                       */
  U16 Tout;                       /* Receive timer value                     */
  void *buf_list;                 /* Rx Data buffer chain                    */
} BSD_INFO;

typedef struct http_info {        /* << HTTP Session info >>                 */
  U8  State;                      /* HTTP Session current state              */
  U8  Socket;                     /* binded TCP Socket                       */
  U16 Flags;                      /* State machine Flags                     */
  U8  FType;                      /* File Type: html, jpeg, gif,...          */
  U8  PostSt;                     /* POST method Processing Status           */
  U16 DelimSz;                    /* Boundary delimiter size                 */
  U8  UserId;                     /* User Id (authentication enabled)        */
  U32 CGIvar;                     /* CGI session private variable (cgi_func) */
  U32 DLen;                       /* Data length (number of bytes to send)   */
  U32 Count;                      /* Total number of bytes sent              */
  U16 BCnt;                       /* Number of bytes sent in last packet     */
  U8  Lang[6];                    /* Selected Web Language: en-us, de, fr .. */
  U32 LMDate;                     /* Last Modified Date (UTC format)         */
  U8 *Script;                     /* Script Buffer pointer                   */
  U8 *pDelim;                     /* Multipart Boundary delimiter value      */
  void *sFile;                    /* Script Interpreter File pointer         */
  void *dFile;                    /* Data File pointer                       */
} HTTP_INFO;

typedef struct http_file {        /* << HTTP Internal File info >>           */
  U32       Id;                   /* File Name Id (CRC32 value of file name) */
  const U8 *Start;                /* File Start Address in ROM               */
} const HTTP_FILE;

typedef struct tnet_info {        /* << Telnet Session info >>               */
  U8  State;                      /* Telnet Session current state            */
  U8  Socket;                     /* binded TCP Socket                       */
  U8  Flags;                      /* State machine Flags                     */
  U8  BCnt;                       /* Received Data byte count                */
  U16 Tout;                       /* Timeout delay counter                   */
  U8  UserId;                     /* User Id (authentication enabled)        */
  U8  Widx;                       /* Fifo buffer Write index                 */
  U8  Ridx;                       /* Fifo buffer Read index                  */
  U8  hNext;                      /* History command next position           */
  U8  hCurr;                      /* History command current position        */
  U32 SVar;                       /* Session private var. (tnet_process_cmd) */
  U8  LBuf[TNET_LBUFSZ];          /* Data Line Buffer                        */
  U8  Fifo[TNET_FIFOSZ];          /* Fifo Buffer for received line/keycodes  */
  U8  Hist[TNET_HISTSZ];          /* Command History buffer                  */
} TNET_INFO;

typedef struct tftp_info {        /* << TFTP Session info >>                 */
  U8  State;                      /* TFTP Session current state              */
  U8  Socket;                     /* binded UDP Data Socket                  */
  U8  Flags;                      /* State machine Flags                     */
  U8  Retries;                    /* Retry counter                           */
  U8  RemIpAdr[IP_ADRLEN];        /* Remote IP address                       */
  U16 RemPort;                    /* Remote UDP port (TID)                   */
  U16 BlockSz;                    /* Transfer Block size                     */
  U16 BlockNr;                    /* Block Number                            */
  U8  Timer;                      /* Timeout Timer value                     */
  U16 BufLen;                     /* Length of retransmit buffer             */
  U8  *Buf;                       /* Transmit/Retransmit buffer              */
  void *File;                     /* File Handle pointer                     */
} TFTP_INFO;

typedef struct ftp_info {         /* << FTP Session info >>                  */
  U8  State;                      /* FTP Session current state               */
  U8  Socket;                     /* binded TCP Control Socket               */
  U16 Flags;                      /* State machine Flags                     */
  U8  RemIpAdr[IP_ADRLEN];        /* Client IP address                       */
  U16 DPort;                      /* TCP Data port (Server or Client)        */
  U8  DSocket;                    /* TCP Data Socket                         */
  U8  UserId;                     /* User Id (authentication enabled)        */
  U8  Resp;                       /* FTP Server Response Code                */
  U8  PathLen;                    /* Size of the Path string                 */
  U8 *Path;                       /* Current Working Directory               */
  U8 *Name;                       /* Absolute File/Folder Path Name          */
  void *File;                     /* File Handle pointer                     */
} FTP_INFO;

typedef struct dns_cache {        /* << DNS Cache Entry info >>              */
  U32 HostId;                     /* Host Id (CRC32 value of host name)      */
  U32 Ttl;                        /* Cache Entry Time To Live                */
  U8  IpAdr[IP_ADRLEN];           /* Ethernet IP Address                     */
} DNS_CACHE;

typedef struct localm {           /* << Local Machine info >>                */
  U8  IpAdr[IP_ADRLEN];           /* Local IP Address                        */
  U8  DefGW[IP_ADRLEN];           /* Default GateWay                         */
  U8  NetMask[IP_ADRLEN];         /* Net Mask                                */
  U8  PriDNS[IP_ADRLEN];          /* Primary DNS Server                      */
  U8  SecDNS[IP_ADRLEN];          /* Secondary DNS Server                    */
} LOCALM;

typedef struct remotem {          /* << Remote Machine Info >>               */
  U8  IpAdr[IP_ADRLEN];           /* Remote IP address                       */
  U8  HwAdr[ETH_ADRLEN];          /* Remote Hardware Address                 */
} REMOTEM;

typedef struct mib_entry {        /* << SNMP-MIB Entry Info >>               */
  U8  Type;                       /* Object Type                             */
  U8  OidLen;                     /* Object ID length                        */
  U8  Oid[MIB_OIDSZ];             /* Object ID value                         */
  U8  ValSz;                      /* Size of a Variable                      */
  void *Val;                      /* Pointer to a variable                   */
  void (*cb_func)(int mode);      /* Write/Read event callback function      */
} MIB_ENTRY;

typedef struct sys_cfg {          /* << SYS Configuration info >>            */
  U32 *MemPool;                   /* Dynamic Memory Pool buffer              */
  U32 MemSize;                    /* Memory Pool size in bytes               */
  U8  TickRate;                   /* Tick Rate in ticks per second           */
  U8  TickItv;                    /* Tick Interval in ms                     */
  U8  T200ms;                     /* Delay 200 ms in ticks                   */
  U8  NetCfg;                     /* Network Interface Configuration flags   */
  U8 *HostName;                   /* Local Host Name                         */
} const SYS_CFG;

typedef struct arp_cfg {          /* << ARP Configuration info >>            */
  ARP_INFO *Table;                /* Cache Table array                       */
  U8  TabSize;                    /* Cache Table size                        */
  U8  TimeOut;                    /* Table Entry expiration time in seconds  */
  U8  MaxRetry;                   /* Number of Retries to resolve MAC addr.  */
  U8  Resend;                     /* Resend Timeout in seconds               */
  U8  Notify;                     /* Notify on IP address changes             */
} const ARP_CFG;

typedef struct igmp_cfg {         /* << IGMP Configuration info >>           */
  IGMP_INFO *Table;               /* Group Table array                       */
  U16 TabSize;                    /* Group Table size                        */
} const IGMP_CFG;

typedef struct dhcp_cfg {         /* << DHCP Configuration info >>           */
  U8 *Vcid;                       /* Vendor Class Identifier                 */
  U8  Opt;                        /* Extra DHCP option flags                 */
} const DHCP_CFG;

typedef struct ppp_cfg {          /* << PPP Configuration info >>            */
  U32 ACCmap;                     /* Async Control Character map             */
  U16 SerTout;                    /* Serial Frame Receive Timeout            */
  U16 RetryTout;                  /* Retry Timeout in ticks                  */
  U16 EchoTout;                   /* LCP Echo Timeout in seconds             */
  U8  MaxRetry;                   /* Number of Retries                       */
  U8  EnAuth;                     /* Enabled Authentication protocols        */
} const PPP_CFG;

typedef struct udp_cfg {          /* << UDP Configuration info >>            */
  UDP_INFO *Scb;                  /* Socket Control Block array              */
  U8  NumSocks;                   /* Number of UDP Sockets                   */
} const UDP_CFG;

typedef struct tcp_cfg {          /* << TCP Configuration info >>            */
  TCP_INFO *Scb;                  /* Socket Control Block array              */
  U8  NumSocks;                   /* Number of TCP Sockets                   */
  U8  MaxRetry;                   /* Number of Retries                       */
  U16 RetryTout;                  /* Retry Timeout in ticks                  */
  U16 T2MSLTout;                  /* Maximum Segment Life Time               */
  U16 SynRetryTout;               /* SYN Retry Timeout in ticks              */
  U16 InitRetryTout;              /* Initial Retransmit timeout in ticks     */
  U16 DefTout;                    /* Default Connect Timeout in seconds      */
  U16 MaxSegSize;                 /* Maximum Segment Size value              */
  U16 RecWinSize;                 /* Receiving Window Size in bytes          */
  U8  ConRetry;                   /* Number of Retries to Connect            */
} const TCP_CFG;

typedef struct http_cfg {         /* << HTTP Configuration info >>           */
  HTTP_INFO *Scb;                 /* Session Control Block array             */
  U8  NumSess;                    /* Max. Number of Active Sessions          */
  U8  EnAuth;                     /* Enable User Authentication              */
  U16 PortNum;                    /* Listening Port number                   */
  U8 const *SrvId;                /* Server-Id http header                   */
  U8 const *Realm;                /* Authentication Realm                    */
  U8 const *User;                 /* Authentication User name                */
  U8 *Passw;                      /* Authentication Password                 */
} const HTTP_CFG;

typedef struct tnet_cfg {         /* << TNET Configuration info >>           */
  TNET_INFO *Scb;                 /* Session Control Block array             */
  U8  NumSess;                    /* Max. Number of Active Sessions          */
  U8  EnAuth;                     /* Enable User Authentication              */
  U8  NoEcho;                     /* Disable Server Echo mode                */
  U16 PortNum;                    /* Listening Port number                   */
  U16 IdleTout;                   /* Idle Connection timeout in ticks        */
  U8 const *User;                 /* Authentication User Name                */
  U8 *Passw;                      /* Authentication Password                 */
} const TNET_CFG;

typedef struct tftp_cfg {         /* << TFTP Configuration info >>           */
  TFTP_INFO *Scb;                 /* Session Control Block array             */
  U8  NumSess;                    /* Max. Number of Active Sessions          */
  U8  MaxRetry;                   /* Number of Retries                       */
  U16 PortNum;                    /* Listening Port number                   */
  U8  DefTout;                    /* Inactive Session Timeout in seconds     */
  U8  EnFwall;                    /* Enable Firewall Support                 */
} const TFTP_CFG;

typedef struct tftpc_cfg {        /* << TFTPC Configuration info >>          */
  U16 BlockSize;                  /* Transfer Block size                     */
  U16 RetryTout;                  /* Retry Timeout in ticks                  */
  U8  MaxRetry;                   /* Number of Retries                       */
} const TFTPC_CFG;

typedef struct ftp_cfg {          /* << FTP Configuration info >>            */
  FTP_INFO *Scb;                  /* Session Control Block array             */
  U8  NumSess;                    /* Max. Number of Active Sessions          */
  U8  EnAuth;                     /* Enable User Authentication              */
  U16 PortNum;                    /* Listening Port number                   */
  U16 IdleTout;                   /* Idle Connection timeout in ticks        */
  U8  MsgLen;                     /* Length of welcome message               */
  U8 const *Msg;                  /* Server Welcome message                  */ 
  U8 const *User;                 /* Authentication User Name                */
  U8 *Passw;                      /* Authentication Password                 */
} const FTP_CFG;

typedef struct ftpc_cfg {         /* << FTPC Configuration info >>           */
  U8  DefTout;                    /* Default inactivity timeout              */
  U8  PasvMode;                   /* FTP Passive Mode used                   */
} const FTPC_CFG;

typedef struct dns_cfg {          /* << DNS Configuration info >>            */
  DNS_CACHE *Table;               /* Cache Table array                       */
  U8  TabSize;                    /* Cache Table size                        */
} const DNS_CFG;

typedef struct snmp_cfg {         /* << SNMP Configuration info >>           */
  U16 PortNum;                    /* Listening Port number                   */
  U16 TrapPort;                   /* Trap Port number                        */
  U8  TrapIp[IP_ADRLEN];          /* Trap Server IP Address                  */
  U8 const *Community;            /* Community Name                          */
  U8  TickItv;                    /* Tick Interval in ticks                  */
} const SNMP_CFG;

typedef struct sntp_cfg {         /* << SNTP Configuration info >>           */
  U8  SrvIp[IP_ADRLEN];           /* NTP/SNTP Server IP Address              */
  U8  Bcast;                      /* Broadcast client mode (for LAN only)    */
} const SNTP_CFG;

typedef struct bsd_cfg {          /* << BSD Configuration info >>            */
  BSD_INFO *Scb;                  /* Socket Control Block array              */
  U8  NumSocks;                   /* Number of BSD Sockets                   */
  U8  InRtx;                      /* Running in RTX environment              */
  U16 RcvTout;                    /* Blocking recv timeout in ticks          */
} const BSD_CFG;

typedef enum {                    /* << Fatal System Error Codes >>          */
  ERR_MEM_ALLOC,                  /* Alloc memory failed, out of memory      */
  ERR_MEM_FREE,                   /* Free memory failed, memory slot invalid */
  ERR_MEM_CORRUPT,                /* Memory corruption detected              */
  ERR_MEM_LOCK,                   /* Locked memory function re-entered error */
  ERR_UDP_ALLOC,                  /* No free UDP sockets available           */
  ERR_TCP_ALLOC,                  /* No free TCP sockets available           */
  ERR_TCP_STATE                   /* TCP socket in undefined state           */
} ERROR_CODE;


/*----------------------------------------------------------------------------
 *      Functions
 *---------------------------------------------------------------------------*/

/* Net_Config.c */
extern void init_system (void);
extern void run_system (void);
extern void sys_error (ERROR_CODE code);

/* at_Mem.c */
extern OS_FRAME *alloc_mem (U32 byte_size);
extern void free_mem (OS_FRAME *mem_ptr);

/* at_Ethernet.c */
extern void eth_init_link (void);
extern void eth_run_link (void);
extern void put_in_queue (OS_FRAME *frame);
extern BOOL eth_send_frame (OS_FRAME *frame);
extern BOOL eth_chk_adr (OS_FRAME *frame);
extern U8  *eth_get_adr (U8 *ipadr);

/* at_Ppp.c */
extern void ppp_init_link (void);
extern void ppp_run_link (void);
extern BOOL ppp_send_frame (OS_FRAME *frame, U16 prot);

/* at_Ppp_Pap.c */
extern void pap_init (void);
extern void pap_process (OS_FRAME *frame);
extern void pap_run (void);

/* at_Ppp_Chap.c */
extern void chap_init (void);
extern void chap_process (OS_FRAME *frame);
extern void chap_run (void);

/* at_Slip.c */
extern void slip_init_link (void);
extern void slip_run_link (void);
extern BOOL slip_send_frame (OS_FRAME *frame);

/* at_Lib.c */
extern int  mem_copy (void *dp, void *sp, int len);
extern void mem_rcopy (void *dp, void *sp, int len);
extern BOOL mem_comp (void *sp1, void *sp2, int len);
extern void mem_set (void *dp, U8 val, int len);
extern BOOL mem_test (void *sp, U8 val, int len);
extern BOOL str_scomp (U8 *sp, U8 const *cp);
extern int  str_copy (U8 *dp, U8 *sp);
extern void str_up_case (U8 *dp, U8 *sp);

/* at_Arp.c */
extern void arp_notify (void);
extern BOOL arp_get_info (REMOTEM *info);

/* at_Ip.c */
extern void ip_init (void);
extern void ip_run_local (void);

/* at_Dhcp.c */
extern void dhcp_cbfunc (U8 opt, U8 *val, U16 len);

/* at_Icmp.c */
extern void icmp_init (void);
extern void icmp_run_engine (void);

/* at_Igmp.c */
extern void igmp_init (void);
extern void igmp_run_host (void);
extern void igmp_process (OS_FRAME *frame);

/* at_Udp.c */
extern void udp_init (void);
extern void udp_process (OS_FRAME *frame);

/* at_Tcp.c */
extern void tcp_init (void);
extern void tcp_poll_sockets (void);
extern void tcp_process (OS_FRAME *frame);

/* at_Bsd.c */
extern void bsd_init (void);
extern void bsd_poll_sockets (void);
extern U8   bsd_wait (BSD_INFO *bsd_s, U8 evt);
extern void bsd_enable (BSD_INFO *bsd_s, U8 evt);

/* at_Bsd_Host.c */
extern void bsd_init_host (void);

/* at_Http.c */
extern void http_init (void);
extern void http_run_server (void);
extern void *http_fopen (U8 *name);
extern void http_fclose (void *file);
extern U16  http_fread (void *file, U8 *buf, U16 len);
extern BOOL http_fgets (void *file, U8 *buf, U16 size);
extern U32  http_finfo (U8 *name);
extern void cgi_process_var (U8 *qstr);
extern void cgi_process_data (U8 code, U8 *dat, U16 len);
extern U16  cgi_func (U8 *env, U8 *buf, U16 buflen, U32 *pcgi);
extern U8  *cgx_content_type (void);
extern U8  *http_encoding (void);
extern BOOL http_accept_host (U8 *rem_ip, U16 rem_port);
extern BOOL http_file_access (U8 *fname, U8 user_id);
extern U8   http_check_account (U8 *user, U8 *passw);
extern U8  *http_get_var (U8 *env, void *ansi, U16 maxlen);
extern U8  *http_get_lang (void);
extern void http_get_info (REMOTEM *info);
extern U8   http_get_session (void);
extern U8   http_get_user_id (void);
extern U8  *http_get_content_type (void);
extern U32  http_date (RL_TIME *time);

/* at_Telnet.c */
extern void tnet_init (void);
extern void tnet_run_server (void);
extern U16  tnet_cbfunc (U8 code, U8 *buf, U16 buflen);
extern U16  tnet_process_cmd (U8 *cmd, U8 *buf, U16 buflen, U32 *pvar);
extern BOOL tnet_ccmp (U8 *buf, U8 *cmd);
extern void tnet_set_delay (U16 dly);
extern void tnet_get_info (REMOTEM *info);
extern U8   tnet_get_session (void);
extern U8   tnet_get_user_id (void);
extern BOOL tnet_msg_poll (U8 session);
extern BOOL tnet_accept_host (U8 *rem_ip, U16 rem_port);
extern U8   tnet_check_account (U8 code, U8 *id);

/* at_Tftp.c */
extern void tftp_init (void);
extern void tftp_run_server (void);
extern void *tftp_fopen (U8 *fname, U8 *mode);
extern void tftp_fclose (void *file);
extern U16  tftp_fread (void *file, U8 *buf, U16 len);
extern U16  tftp_fwrite (void *file, U8 *buf, U16 len);
extern BOOL tftp_accept_host (U8 *rem_ip, U16 rem_port);

/* at_Tftpc.c */
extern void tftpc_init (void);
extern void tftpc_run_client (void);
extern void *tftpc_fopen (U8 *fname, U8 *mode);
extern void tftpc_fclose (void *file);
extern U16  tftpc_fread (void *file, U8 *buf, U16 len);
extern U16  tftpc_fwrite (void *file, U8 *buf, U16 len);

/* at_Ftp.c */
extern void ftp_init (void);
extern void ftp_run_server (void);
extern void *ftp_fopen (U8 *fname, U8 *mode);
extern void ftp_fclose (void *file);
extern U16  ftp_fread (void *file, U8 *buf, U16 len);
extern U16  ftp_fwrite (void *file, U8 *buf, U16 len);
extern BOOL ftp_fdelete (U8 *fname);
extern BOOL ftp_frename (U8 *fname, U8 *newn);
extern U16  ftp_ffind (U8 code, U8 *buf, U8 *mask, U16 len);
extern BOOL ftp_accept_host (U8 *rem_ip, U16 rem_port);
extern U8   ftp_check_account (U8 code, U8 *id);
extern U8   ftp_get_user_id (void);
extern BOOL ftp_file_access (U8 *fname, U8 mode, U8 user_id);
extern void ftp_evt_notify (U8 evt);

/* at_Ftpc.c */
extern void ftpc_init (void);
extern void ftpc_run_client (void);
extern void *ftpc_fopen (U8 *mode);
extern void ftpc_fclose (void *file);
extern U16  ftpc_fread (void *file, U8 *buf, U16 len);
extern U16  ftpc_fwrite (void *file, U8 *buf, U16 len);
extern U16  ftpc_cbfunc (U8 code, U8 *buf, U16 buflen);

/* at_Dhcp.c */
extern void dhcp_init (void);
extern void dhcp_run_client (void);
#define init_dhcp   dhcp_init

/* at_Nbns.c */
extern void nbns_init (void);

/* at_Dns.c */
extern void dns_init (void);
extern void dns_run_client (void);
extern U8   get_host_by_name (U8 *hostn, void (*cbfunc)(U8, U8 *));

/* at_Smtp.c */
extern void smtp_init (void);
extern void smtp_run_client (void);
extern U16  smtp_cbfunc (U8 code, U8 *buf, U16 buflen, U32 *pvar);
extern BOOL smtp_accept_auth (U8 *srv_ip);

/* at_Snmp.c */
extern void snmp_init (void);
extern void snmp_run_agent (void);

/* at_Sntp.c */
extern void sntp_init (void);
extern void sntp_run_client (void);

/* Ethernet Device Driver */
extern void init_ethernet (void);
extern void send_frame (OS_FRAME *frame);
__weak void poll_ethernet (void);
extern void int_enable_eth (void);
extern void int_disable_eth (void);

/* Serial Device Driver */
extern void init_serial (void);
extern int  com_getchar (void);
extern BOOL com_putchar (U8 c);
extern BOOL com_tx_active (void);

/* Modem Device Driver */
extern void modem_init (void);
extern void modem_dial (U8 *dialnum);
extern void modem_hangup (void);
extern void modem_listen (void);
extern BOOL modem_online (void);
extern BOOL modem_process (U8 ch);
extern void modem_run (void);

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/

#endif

