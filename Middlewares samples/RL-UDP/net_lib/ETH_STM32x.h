/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    ETH_STM32X.H
 *      Purpose: ST STM32F105/107 Ethernet Controller Driver definitions
 *      Rev.:    V4.70
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2013 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#ifndef __ETH_STM32X_H
#define __ETH_STM32X_H

/* ETH Memory Buffer configuration. */
#define NUM_RX_BUF          4           /* 0x1800 for Rx (4*1536=6K)         */
#define NUM_TX_BUF          2           /* 0x0600 for Tx (2*1536=3K)         */
#define ETH_BUF_SIZE        1536        /* ETH Receive/Transmit buffer size  */

/* DMA Descriptors. */
typedef struct {
  U32 volatile Stat;
  U32 Ctrl;
  U32 Addr;
  U32 Next;
} RX_Desc;

typedef struct {
  U32 volatile CtrlStat;
  U32 Size;
  U32 Addr;
  U32 Next;
} TX_Desc;

/* MAC Configuration Register */
#define MCR_WD              0x00800000  /* Watchdog disable                  */
#define MCR_JD              0x00400000  /* Jabber disable                    */
#define MCR_IFG             0x000E0000  /* Interframe gap mask               */
#define MCR_CSD             0x00010000  /* Carrier sense disable             */
#define MCR_FES             0x00004000  /* Fast 100 Mb ethernet speed        */
#define MCR_ROD             0x00002000  /* Receive own disable               */
#define MCR_LM              0x00001000  /* Loopback mode                     */
#define MCR_DM              0x00000800  /* Duplex mode                       */
#define MCR_IPCO            0x00000400  /* IPv4 checksum offload             */
#define MCR_RD              0x00000200  /* Retry disable                     */
#define MCR_APCS            0x00000080  /* Automatic pad / CRC stripping     */
#define MCR_BL              0x00000060  /* Back-off limit mask               */
#define MCR_DC              0x00000010  /* Deferral check                    */
#define MCR_TE              0x00000008  /* Transmitter enable                */
#define MCR_RE              0x00000004  /* Receiver enable                   */

/* MAC Frame Filter Register */
#define MFFR_RA             0x80000000  /* Receive all                       */
#define MFFR_HPF            0x00000400  /* Hash or Perfect filter            */
#define MFFR_SAF            0x00000200  /* Source address filter             */
#define MFFR_SAIF           0x00000100  /* Source address inverse filtering  */
#define MFFR_PCF            0x000000C0  /* Pass control frames mask          */
#define MFFR_BFD            0x00000020  /* Broadcast frames disable          */
#define MFFR_PAM            0x00000010  /* Pass all multicast                */
#define MFFR_DAIF           0x00000008  /* Dest. address inverse filtering   */
#define MFFR_HM             0x00000004  /* Hash multicast                    */
#define MFFR_HU             0x00000002  /* Hash unicast                      */
#define MFFR_PM             0x00000001  /* Promiscuous mode                  */

/* MAC MII Address Register */
#define MMAR_PA             0x0000F800  /* PHY address mask                  */
#define MMAR_MR             0x000007C0  /* MII register address mask         */
#define MMAR_CR             0x0000001C  /* Clock range                       */
#define MMAR_MW             0x00000002  /* MII write                         */
#define MMAR_MB             0x00000001  /* MII busy                          */

/* MAC MII Data Register */
#define MMDR_MD             0x0000FFFF  /* MII 16-bit rw data                */

/* MII Management Time out values */
#define MII_WR_TOUT         0x00050000  /* MII Write timeout count           */
#define MII_RD_TOUT         0x00050000  /* MII Read timeout count            */

/* MAC Flow Control Register */
#define MFCR_PT             0xFFFF0000  /* Pause time mask                   */
#define MFCR_ZQPD           0x00000080  /* Zero-quanta pause disable         */
#define MFCR_PLT            0x00000030  /* Pause low threshold               */
#define MFCR_UPFD           0x00000008  /* Unicaste pause frame detect       */
#define MFCR_RFCE           0x00000004  /* Receive flow control enable       */
#define MFCR_TFCE           0x00000002  /* Transmit flow control enable      */
#define MFCR_FCB_BPA        0x00000001  /* Flow ctrl busy/back pressure act. */

/* MAC VLAN Tag Register */
#define MVTR_VLANTC         0x00010000  /* 12-bit VLAN tag comparison        */
#define MVTR_VLANTI         0x0000FFFF  /* VLAN tag identifier for rx frames */

/* MAC PMT Contrl and Status Register */
#define MPCSR_WFFRPR        0x80000000  /* Wakeup frame filter reg.ptr reset */
#define MPCSR_GU            0x00000200  /* Global unicast                    */
#define MPCSR_WFR           0x00000040  /* Wakeup frame received             */
#define MPCSR_MPR           0x00000020  /* Magic packet received             */
#define MPCSR_WFE           0x00000004  /* Wakeup frame enable               */
#define MPCSR_MPE           0x00000002  /* Magic packet enable               */
#define MPCSR_PD            0x00000001  /* Power down                        */

/* MAC Interrupt Status Register */
#define MSR_TSTS            0x00000200  /* Time stamp trigger status         */
#define MSR_MMCTS           0x00000040  /* MMC transmit status               */
#define MSR_MMCRS           0x00000020  /* MMC receive status                */
#define MSR_MMCS            0x00000010  /* MMC status                        */
#define MSR_PMTS            0x00000008  /* PMT status                        */

/* MAC Interrupt Mask Register */
#define MIMR_TSTIM          0x00000200  /* Time stamp trigger mask           */
#define MIMR_PMTIM          0x00000008  /* PMT interrupt mask                */

/* MAC Address Hi Control bits */
#define MADR_AE             0x80000000  /* Address enable                    */
#define MADR_SA             0x40000000  /* Source address compare            */
#define MADR_MBC            0x3F000000  /* Mask byte control                 */
#define MADR_AH             0x0000FFFF  /* MAC Address high                  */

/* MMC Control Register */
#define MMCR_MCF            0x00000008  /* MMC counter freeze                */
#define MMCR_ROR            0x00000004  /* Reset on read                     */
#define MMCR_CSR            0x00000002  /* Counter stop rollover             */
#define MMCR_CR             0x00000001  /* Counter reset                     */

/* MMC Receive Interrupt/Mask Registers */
#define MMRI_RGUFS          0x00020000  /* Received good ucast frames status */
#define MMRI_RFAES          0x00000040  /* Received frames align.error status*/
#define MMRI_RFCES          0x00000020  /* Receive frames CRC error status   */

/* MMC Transmit Interrupt/Mask Registers */
#define MMTIR_TGFS          0x00200000  /* Transmitted good frames status    */
#define MMTIR_TGFMSCS       0x00008000  /* Tx good frm.more single col.status*/
#define MMTIR_TGFSCS        0x00004000  /* Tx good frm.single collision stat.*/

/* PTP Time Stamp Register */
#define PTSCR_TTSARU        0x00000020  /* Time stamp addend register update */
#define PTSCR_TSITE         0x00000010  /* TS interrupt trigger enable       */
#define PTSCR_TSSTU         0x00000008  /* TS system time update             */
#define PTSCR_TSSTI         0x00000004  /* TS system time initialize         */
#define PTSCR_TSFCU         0x00000002  /* TS fine or coarse update          */
#define PTSCR_TSE           0x00000001  /* Time stamp enable                 */

/* DMA Bus Mode Register */
#define DBMR_AAB            0x02000000  /* Address-aligned beats             */
#define DBMR_FPM            0x01000000  /* 4xPBL mode                        */
#define DBMR_USP            0x00800000  /* Use separate PBL                  */
#define DBMR_RDP            0x007E0000  /* Rx DMA PBL mask                   */
#define DBMR_FB             0x00010000  /* Fixed burst                       */
#define DBMR_RTPR           0x0000C000  /* Rx Tx priority ratio              */
#define DBMR_PBL            0x00003F00  /* Programmable burst length mask    */
#define DBMR_DSL            0x0000007C  /* Descriptor skip length            */
#define DBMR_DA             0x00000002  /* DMA arbitration                   */
#define DBMR_SR             0x00000001  /* Software reset                    */

/* DMA Status Register */
#define DSR_TSTS            0x20000000  /* Timestamp trigger status          */
#define DSR_PMTS            0x10000000  /* PMT status                        */
#define DSR_MMCS            0x08000000  /* MMC status                        */
#define DSR_EBS             0x03800000  /* Error bits status mask            */
#define DSR_TPS             0x00700000  /* Transmit process state            */
#define DSR_RPS             0x000E0000  /* Receive process state             */
#define DSR_NIS             0x00010000  /* Normal interrupt summary          */
#define DSR_AIS             0x00008000  /* Abnormal interrupt summary        */
#define DSR_ERS             0x00004000  /* Early receive status              */
#define DSR_FBES            0x00002000  /* Fatal bus error status            */
#define DSR_ETS             0x00000400  /* Early transmit status             */
#define DSR_RWTS            0x00000200  /* Receive watchdog timeout status   */
#define DSR_RPSS            0x00000100  /* Receive process stopped status    */
#define DSR_RBUS            0x00000080  /* Receive buffer unavailable status */
#define DSR_RS              0x00000040  /* Receive status                    */
#define DSR_TUS             0x00000020  /* Transmit underflow status         */
#define DSR_ROS             0x00000010  /* Receive overflow status           */
#define DSR_TJTS            0x00000008  /* Transmit jabber timeout status    */
#define DSR_TBUS            0x00000004  /* Transmit buffer unavailable status*/
#define DSR_TPSS            0x00000002  /* Transmit process stopped status   */
#define DSR_TS              0x00000001  /* Transmit status                   */

/* DMA Operation Mode Register */
#define DOMR_DTCEFD         0x04000000  /* Dropping of TCP/IP chksum err dis.*/
#define DOMR_RSF            0x02000000  /* Receive store and forward         */
#define DOMR_DFRF           0x01000000  /* Disable flushing of received frms */
#define DOMR_TSF            0x00200000  /* Transmit storea and forward       */
#define DOMR_FTF            0x00100000  /* Flush transmit FIFO               */
#define DOMR_TTC            0x0001C000  /* Transmit treshold control mask    */
#define DOMR_ST             0x00002000  /* Start/stop transmission           */
#define DOMR_FEF            0x00000080  /* Forward error frames              */
#define DOMR_FUGF           0x00000040  /* Forward undersized good frames    */
#define DOMR_RTC            0x00000018  /* Receive threshold control mask    */
#define DOMR_OSF            0x00000004  /* Operate on second frame           */
#define DOMR_SR             0x00000002  /* Start/stop receive                */

/* DMA Interrupt Enable Register */
#define INT_NISE            0x00010000  /* Normal interrupt summary          */
#define INT_AISE            0x00008000  /* Abnormal interrupt summary        */
#define INT_ERIE            0x00004000  /* Early receive interrupt           */
#define INT_FBEIE           0x00002000  /* Fatal bus error interrupt         */
#define INT_ETIE            0x00000400  /* Early transmit interrupt          */
#define INT_RWTIE           0x00000200  /* Receive watchdog timeout interrupt*/
#define INT_RPSIE           0x00000100  /* Receive process stopped intterrupt*/
#define INT_RBUIE           0x00000080  /* Receive buffer unavailable inter. */
#define INT_RIE             0x00000040  /* Receive interrupt                 */
#define INT_TUIE            0x00000020  /* Transmit underflow interrupt      */
#define INT_ROIE            0x00000010  /* Receive overflow interrupt        */
#define INT_TJTIE           0x00000008  /* Transmit jabber timeout interrupt */
#define INT_TBUIE           0x00000004  /* Transmit buffer unavailable inter.*/
#define INT_TPSIE           0x00000002  /* Transmit process stopped interrupt*/
#define INT_TIE             0x00000001  /* Transmit interrupt                */

/* DMA Missed Frame and Buffer Overflow Counter Register */
#define DMFBOC_OFOC         0x10000000  /* Overflow bit for FIFO ovfl cntr.  */
#define DMFBOC_MFA          0x0FFE0000  /* Missed frames by the application  */
#define DMFBOC_OMFC         0x00010000  /* Ovfl bit for missed frame counter */
#define DMFBOC_MFC          0x0000FFFF  /* Missed frames by controller       */

/* DMA Descriptor TX Packet Control/Status */
#define DMA_TX_OWN          0x80000000  /* Own bit 1=DMA,0=CPU               */
#define DMA_TX_IC           0x40000000  /* Interrupt on completition         */
#define DMA_TX_LS           0x20000000  /* Last segment                      */
#define DMA_TX_FS           0x10000000  /* First segment                     */
#define DMA_TX_DC           0x08000000  /* Disable CRC                       */
#define DMA_TX_DP           0x04000000  /* Disable pad                       */
#define DMA_TX_TTSE         0x02000000  /* Transmit time stamp enable        */
#define DMA_TX_CIC          0x00C00000  /* Checksum insertion control        */
#define DMA_TX_TER          0x00200000  /* Transmit end of ring              */
#define DMA_TX_TCH          0x00100000  /* Second address chained            */
#define DMA_TX_TTSS         0x00020000  /* Transmit time stamp status        */
#define DMA_TX_IHE          0x00010000  /* IP header error status            */
#define DMA_TX_ES           0x00008000  /* Error summary                     */
#define DMA_TX_JT           0x00004000  /* Jabber timeout                    */
#define DMA_TX_FF           0x00002000  /* Frame flushed                     */
#define DMA_TX_IPE          0x00001000  /* IP payload error                  */
#define DMA_TX_LC           0x00000800  /* Loss of carrier                   */
#define DMA_TX_NC           0x00000400  /* No carrier                        */
#define DMA_TX_LCOL         0x00000200  /* Late collision                    */
#define DMA_TX_EC           0x00000100  /* Excessive collision               */
#define DMA_TX_VF           0x00000080  /* VLAN frame                        */
#define DMA_TX_CC           0x00000078  /* Collision count                   */
#define DMA_TX_ED           0x00000004  /* Excessive deferral                */
#define DMA_TX_UF           0x00000002  /* Underflow error                   */
#define DMA_TX_DB           0x00000001  /* Deferred bit                      */

/* DMA Descriptor RX Packet Status */
#define DMA_RX_OWN          0x80000000  /* Own bit 1=DMA,0=CPU               */
#define DMA_RX_AFM          0x40000000  /* Destination address filter fail   */
#define DMA_RX_FL           0x3FFF0000  /* Frame length mask                 */
#define DMA_RX_ES           0x00008000  /* Error summary                     */
#define DMA_RX_DE           0x00004000  /* Descriptor error                  */
#define DMA_RX_SAF          0x00002000  /* Source address filter fail        */
#define DMA_RX_LE           0x00001000  /* Length error                      */
#define DMA_RX_OE           0x00000800  /* Overflow error                    */
#define DMA_RX_VLAN         0x00000400  /* VLAN tag                          */
#define DMA_RX_FS           0x00000200  /* First descriptor                  */
#define DMA_RX_LS           0x00000100  /* Last descriptor                   */
#define DMA_RX_IPHCE        0x00000080  /* IPv4 header checksum error        */
#define DMA_RX_LC           0x00000040  /* late collision                    */
#define DMA_RX_FT           0x00000020  /* Frame type                        */
#define DMA_RX_RWT          0x00000010  /* Receive watchdog timeout          */
#define DMA_RX_RE           0x00000008  /* Receive error                     */
#define DMA_RX_DRE          0x00000004  /* Dribble bit error                 */
#define DMA_RX_CE           0x00000002  /* CRC error                         */
#define DMA_RX_RMAM         0x00000001  /* Rx MAC adr.match/payload cks.error*/

#define DMA_RX_ERROR_MASK   (DMA_RX_ES | DMA_RX_LE | DMA_RX_RWT | \
                             DMA_RX_RE | DMA_RX_CE)
#define DMA_RX_SEG_MASK     (DMA_RX_FS | DMA_RX_LS)

/* DMA Descriptor RX Packet Control */
#define DMA_RX_DIC          0x80000000  /* Disable interrupt on completition */
#define DMA_RX_RBS2         0x1FFF0000  /* Receive buffer 2 size             */
#define DMA_RX_RER          0x00008000  /* Receove end of ring               */
#define DMA_RX_RCH          0x00004000  /* Second address chained            */
#define DMA_RX_RBS1         0x00003FFF  /* Receive buffer 1 size             */

/* DP83848C PHY Registers */
#define PHY_REG_BMCR        0x00        /* Basic Mode Control Register       */
#define PHY_REG_BMSR        0x01        /* Basic Mode Status Register        */
#define PHY_REG_IDR1        0x02        /* PHY Identifier 1                  */
#define PHY_REG_IDR2        0x03        /* PHY Identifier 2                  */
#define PHY_REG_ANAR        0x04        /* Auto-Negotiation Advertisement    */
#define PHY_REG_ANLPAR      0x05        /* Auto-Neg. Link Partner Abitily    */
#define PHY_REG_ANER        0x06        /* Auto-Neg. Expansion Register      */
#define PHY_REG_ANNPTR      0x07        /* Auto-Neg. Next Page TX            */

/* PHY Extended Registers */
#define PHY_REG_STS         0x10        /* Status Register                   */
#define PHY_REG_MICR        0x11        /* MII Interrupt Control Register    */
#define PHY_REG_MISR        0x12        /* MII Interrupt Status Register     */
#define PHY_REG_FCSCR       0x14        /* False Carrier Sense Counter       */
#define PHY_REG_RECR        0x15        /* Receive Error Counter             */
#define PHY_REG_PCSR        0x16        /* PCS Sublayer Config. and Status   */
#define PHY_REG_RBR         0x17        /* RMII and Bypass Register          */
#define PHY_REG_LEDCR       0x18        /* LED Direct Control Register       */
#define PHY_REG_PHYCR       0x19        /* PHY Control Register              */
#define PHY_REG_10BTSCR     0x1A        /* 10Base-T Status/Control Register  */
#define PHY_REG_CDCTRL1     0x1B        /* CD Test Control and BIST Extens.  */
#define PHY_REG_EDCR        0x1D        /* Energy Detect Control Register    */

#define PHY_FULLD_100M      0x2100      /* Full Duplex 100Mbit               */
#define PHY_HALFD_100M      0x2000      /* Half Duplex 100Mbit               */
#define PHY_FULLD_10M       0x0100      /* Full Duplex 10Mbit                */
#define PHY_HALFD_10M       0x0000      /* Half Duplex 10MBit                */
#define PHY_AUTO_NEG        0x3000      /* Select Auto Negotiation           */

#define DP83848C_DEF_ADR    0x01        /* Default PHY device address        */
#define DP83848C_ID         0x20005C90  /* PHY Identifier                    */
#endif

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/

