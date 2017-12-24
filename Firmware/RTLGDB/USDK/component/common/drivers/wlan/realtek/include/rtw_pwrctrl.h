/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef __RTW_PWRCTRL_H_
#define __RTW_PWRCTRL_H_


#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
#endif //CONFIG_HAS_EARLYSUSPEND

#define FW_PWR0		0	
#define FW_PWR1 	1
#define FW_PWR2 	2
#define FW_PWR3 	3


#define HW_PWR0		7	
#define HW_PWR1 	6
#define HW_PWR2 	2
#define HW_PWR3		0
#define HW_PWR4		8

#define FW_PWRMSK	0x7


#define XMIT_ALIVE	BIT(0)
#define RECV_ALIVE	BIT(1)
#define CMD_ALIVE	BIT(2)
#define EVT_ALIVE	BIT(3)


enum Power_Mgnt
{
	PS_MODE_ACTIVE	= 0	,
	PS_MODE_MIN		,
	PS_MODE_MAX		,
	PS_MODE_DTIM		,
	PS_MODE_VOIP		,
	PS_MODE_UAPSD_WMM	,
	PS_MODE_UAPSD		,
	PS_MODE_IBSS		,
	PS_MODE_WWLAN		,
	PM_Radio_Off		,
	PM_Card_Disable		,
	PS_MODE_NUM
};


/*
	BIT[2:0] = HW state
	BIT[3] = Protocol PS state,   0: register active state , 1: register sleep state
	BIT[4] = sub-state
*/

#define PS_DPS				BIT(0)
#define PS_LCLK				(PS_DPS)
#define PS_RF_OFF			BIT(1)
#define PS_ALL_ON			BIT(2)
#define PS_ST_ACTIVE		BIT(3)

#define PS_ISR_ENABLE		BIT(4)
#define PS_IMR_ENABLE		BIT(5)
#define PS_ACK				BIT(6)
#define PS_TOGGLE			BIT(7)

#define PS_STATE_MASK		(0x0F)
#define PS_STATE_HW_MASK	(0x07)
#define PS_SEQ_MASK			(0xc0)

#define PS_STATE(x)		(PS_STATE_MASK & (x))
#define PS_STATE_HW(x)	(PS_STATE_HW_MASK & (x))
#define PS_SEQ(x)		(PS_SEQ_MASK & (x))

#define PS_STATE_S0		(PS_DPS)
#define PS_STATE_S1		(PS_LCLK)
#define PS_STATE_S2		(PS_RF_OFF)
#define PS_STATE_S3		(PS_ALL_ON)
#define PS_STATE_S4		((PS_ST_ACTIVE) | (PS_ALL_ON))


#define PS_IS_RF_ON(x)	((x) & (PS_ALL_ON))
#define PS_IS_ACTIVE(x)	((x) & (PS_ST_ACTIVE))
#define CLR_PS_STATE(x)	((x) = ((x) & (0xF0)))


struct reportpwrstate_parm {
	unsigned char mode;
	unsigned char state; //the CPWM value
	unsigned short rsvd;
}; 


typedef _sema _pwrlock;


__inline static void _init_pwrlock(_pwrlock *plock)
{
	rtw_init_sema(plock, 1);
}

__inline static void _free_pwrlock(_pwrlock *plock)
{
	rtw_free_sema(plock);
}


__inline static void _enter_pwrlock(_pwrlock *plock)
{
	rtw_down_sema(plock);
}


__inline static void _exit_pwrlock(_pwrlock *plock)
{
	rtw_up_sema(plock);
}

#define LPS_DELAY_TIME	1 // 1 sec

#define EXE_PWR_NONE	0x01
#define EXE_PWR_IPS		0x02
#define EXE_PWR_LPS		0x04

// RF state.
typedef enum _rt_rf_power_state
{
	rf_on,		// RF is on after RFSleep or RFOff
	rf_sleep,	// 802.11 Power Save mode
	rf_off,		// HW/SW Radio OFF or Inactive Power Save
	//=====Add the new RF state above this line=====//
	rf_max
}rt_rf_power_state;

// RF Off Level for IPS or HW/SW radio off
#define	RT_RF_OFF_LEVL_ASPM			BIT(0)	// PCI ASPM
#define	RT_RF_OFF_LEVL_CLK_REQ		BIT(1)	// PCI clock request
#define	RT_RF_OFF_LEVL_PCI_D3			BIT(2)	// PCI D3 mode
#define	RT_RF_OFF_LEVL_HALT_NIC		BIT(3)	// NIC halt, re-initialize hw parameters
#define	RT_RF_OFF_LEVL_FREE_FW		BIT(4)	// FW free, re-download the FW
#define	RT_RF_OFF_LEVL_FW_32K		BIT(5)	// FW in 32k
#define	RT_RF_PS_LEVEL_ALWAYS_ASPM	BIT(6)	// Always enable ASPM and Clock Req in initialization.
#define	RT_RF_LPS_DISALBE_2R			BIT(30)	// When LPS is on, disable 2R if no packet is received or transmittd.
#define	RT_RF_LPS_LEVEL_ASPM			BIT(31)	// LPS with ASPM

#define	RT_IN_PS_LEVEL(ppsc, _PS_FLAG)		((ppsc->cur_ps_level & _PS_FLAG) ? _TRUE : _FALSE)
#define	RT_CLEAR_PS_LEVEL(ppsc, _PS_FLAG)	(ppsc->cur_ps_level &= (~(_PS_FLAG)))
#define	RT_SET_PS_LEVEL(ppsc, _PS_FLAG)		(ppsc->cur_ps_level |= _PS_FLAG)


enum _PS_BBRegBackup_ {
	PSBBREG_RF0 = 0,
	PSBBREG_RF1,
	PSBBREG_RF2,
	PSBBREG_AFE0,
	PSBBREG_TOTALCNT
};

enum { // for ips_mode
	IPS_NONE=0,
	IPS_NORMAL,
	IPS_LEVEL_2,
	IPS_NUM
};

struct pwrctrl_priv
{
	_pwrlock	lock;
	volatile uint8_t rpwm; // requested power state for fw
	volatile uint8_t cpwm; // fw current power state. updated when 1. read from HCPWM 2. driver lowers power level
	volatile uint8_t tog; // toggling
	volatile uint8_t cpwm_tog; // toggling

	uint8_t	pwr_mode;
	uint8_t	smart_ps;
	uint8_t	bcn_ant_mode;

	uint32_t	alives;
	uint64_t  wowlan_fw_iv;
//TODO
//	_workitem cpwm_event;
#ifdef CONFIG_LPS_RPWM_TIMER
	uint8_t brpwmtimeout;
	_workitem rpwmtimeoutwi;
	_timer pwr_rpwm_timer;
#endif // CONFIG_LPS_RPWM_TIMER
	uint8_t	bpower_saving;

	uint8_t	b_hw_radio_off;
	uint8_t	reg_rfoff;
	uint8_t	reg_pdnmode; //powerdown mode
	uint32_t	rfoff_reason;

	//RF OFF Level
	uint32_t	cur_ps_level;
	uint32_t	reg_rfps_level;



#if defined(CONFIG_PCI_HCI) || defined(CONFIG_LX_HCI)
	//just for PCIE ASPM
	uint8_t	b_support_aspm; // If it supports ASPM, Offset[560h] = 0x40, otherwise Offset[560h] = 0x00. 
	uint8_t	b_support_backdoor;

	//just for PCIE ASPM
	uint8_t	const_amdpci_aspm;
#endif

	uint 	ips_enter_cnts;
	uint 	ips_leave_cnts;

	uint8_t	ps_enable;
	uint8_t	ips_mode; 
	uint8_t	ips_org_mode; 
	uint8_t	ips_mode_req; // used to accept the mode setting request, will update to ipsmode later
	uint bips_processing;
	uint32_t ips_deny_time; /* will deny IPS when system time is smaller than this */
	uint8_t ps_processing; /* temporarily used to mark whether in rtw_ps_processor */

	uint8_t	bLeisurePs;
	uint8_t	LpsIdleCount;
	uint8_t	power_mgnt;
	uint8_t	org_power_mgnt;
	uint8_t	bFwCurrentInPSMode;
	uint32_t	DelayLPSLastTimeStamp;
	uint8_t 	btcoex_rfon;
	int32_t		pnp_current_pwr_state;
	uint8_t		pnp_bstop_trx;


	uint8_t		bInternalAutoSuspend;
	uint8_t		bInSuspend;
#ifdef	CONFIG_BT_COEXIST
	uint8_t		bAutoResume;
	uint8_t		autopm_cnt;
#endif
	uint8_t		bSupportRemoteWakeup;	
#ifdef CONFIG_WOWLAN
	uint8_t      wowlan_txpause_status;
	uint8_t		wowlan_mode;
	uint8_t		wowlan_pattern;
	uint8_t		wowlan_magic;
	uint8_t		wowlan_unicast;
	uint8_t		wowlan_pattern_idx;
	uint8_t		wowlan_wake_reason;
	uint32_t		wowlan_pattern_context[8][5];
#endif // CONFIG_WOWLAN
	_timer 	pwr_state_check_timer;
	int		pwr_state_check_interval;
	uint8_t		pwr_state_check_cnts;

	int 		ps_flag;
	
	rt_rf_power_state	rf_pwrstate;//cur power state
	//rt_rf_power_state 	current_rfpwrstate;
	rt_rf_power_state	change_rfpwrstate;

	uint8_t		wepkeymask;
	uint8_t		bHWPowerdown;//if support hw power down
	uint8_t		bHWPwrPindetect;
	uint8_t		bkeepfwalive;		
	uint8_t		brfoffbyhw;
	unsigned long PS_BBRegBackup[PSBBREG_TOTALCNT];

	#ifdef CONFIG_RESUME_IN_WORKQUEUE
	struct workqueue_struct *rtw_workqueue;
	_workitem resume_work;
	#endif

	#ifdef CONFIG_HAS_EARLYSUSPEND
	struct early_suspend early_suspend;
	uint8_t do_late_resume;
	#endif //CONFIG_HAS_EARLYSUSPEND
	
	#ifdef CONFIG_ANDROID_POWER
	android_early_suspend_t early_suspend;
	uint8_t do_late_resume;
	#endif

	#ifdef CONFIG_INTEL_PROXIM
	uint8_t	stored_power_mgnt;
	#endif

	#ifdef TDMA_POWER_SAVING
	uint8_t	tdma_slot_period;
    uint8_t	tdma_rfon_period_len_1;
    uint8_t	tdma_rfon_period_len_2;
    uint8_t	tdma_rfon_period_len_3;
	#endif

	uint8_t	lps_dtim;
};

#define rtw_get_ips_mode_req(pwrctrlpriv) \
	(pwrctrlpriv)->ips_mode_req

#define rtw_ips_mode_req(pwrctrlpriv, ips_mode) \
	(pwrctrlpriv)->ips_mode_req = (ips_mode)

#define RTW_PWR_STATE_CHK_INTERVAL 2000

#define _rtw_set_pwr_state_check_timer(pwrctrlpriv, ms) \
	do { \
		/*DBG_871X("%s _rtw_set_pwr_state_check_timer(%p, %d)\n", __FUNCTION__, (pwrctrlpriv), (ms));*/ \
		rtw_set_timer(&(pwrctrlpriv)->pwr_state_check_timer, (ms)); \
	} while(0)
	
#define rtw_set_pwr_state_check_timer(pwrctrlpriv) \
	_rtw_set_pwr_state_check_timer((pwrctrlpriv), (pwrctrlpriv)->pwr_state_check_interval)

extern void rtw_init_pwrctrl_priv(_adapter *adapter);
extern void rtw_free_pwrctrl_priv(_adapter * adapter);

#ifdef CONFIG_LPS_LCLK
extern int32_t rtw_register_tx_alive(PADAPTER padapter);
extern void rtw_unregister_tx_alive(PADAPTER padapter);
extern int32_t rtw_register_rx_alive(PADAPTER padapter);
extern void rtw_unregister_rx_alive(PADAPTER padapter);
extern int32_t rtw_register_cmd_alive(PADAPTER padapter);
extern void rtw_unregister_cmd_alive(PADAPTER padapter);
extern int32_t rtw_register_evt_alive(PADAPTER padapter);
extern void rtw_unregister_evt_alive(PADAPTER padapter);
extern void cpwm_int_hdl(PADAPTER padapter, struct reportpwrstate_parm *preportpwrstate);
extern void LPS_Leave_check(PADAPTER padapter);
#endif

extern void rtw_set_ps_mode(PADAPTER padapter, uint8_t ps_mode, uint8_t smart_ps, uint8_t bcn_ant_mode);
extern void rtw_set_rpwm(_adapter * padapter, uint8_t val8);
extern void LeaveAllPowerSaveMode(PADAPTER Adapter);
#ifdef CONFIG_IPS
void ips_enter(_adapter * padapter);
int ips_leave(_adapter * padapter);
#endif

void rtw_ps_processor(_adapter*padapter);

#ifdef CONFIG_AUTOSUSPEND
int autoresume_enter(_adapter* padapter);
#endif
#ifdef SUPPORT_HW_RFOFF_DETECTED
rt_rf_power_state RfOnOffDetect(IN	PADAPTER pAdapter );
#endif


#ifdef CONFIG_LPS
int32_t LPS_RF_ON_check(PADAPTER padapter, uint32_t delay_ms);
void LPS_Enter(PADAPTER padapter);
void LPS_Leave(PADAPTER padapter);
#endif

#ifdef CONFIG_RESUME_IN_WORKQUEUE
void rtw_resume_in_workqueue(struct pwrctrl_priv *pwrpriv);
#endif //CONFIG_RESUME_IN_WORKQUEUE

#if defined(CONFIG_HAS_EARLYSUSPEND ) || defined(CONFIG_ANDROID_POWER)
#define rtw_is_earlysuspend_registered(pwrpriv) (pwrpriv)->early_suspend.suspend
void rtw_register_early_suspend(struct pwrctrl_priv *pwrpriv);
void rtw_unregister_early_suspend(struct pwrctrl_priv *pwrpriv);
#endif //CONFIG_HAS_EARLYSUSPEND || CONFIG_ANDROID_POWER
//TODO
//uint8_t rtw_interface_ps_func(_adapter *padapter,HAL_INTF_PS_FUNC efunc_id,uint8_t* val);
int _rtw_pwr_wakeup(_adapter *padapter, uint32_t ips_deffer_ms, const char *caller);
#define rtw_pwr_wakeup(adapter) _rtw_pwr_wakeup(adapter, RTW_PWR_STATE_CHK_INTERVAL, __FUNCTION__)
int rtw_pm_set_ips(_adapter *padapter, uint8_t mode);
int rtw_pm_set_lps(_adapter *padapter, uint8_t mode);
int rtw_pm_set_tdma_param(_adapter *padapter, uint8_t tdma_slot_period, uint8_t tdma_rfon_period_len_1, uint8_t tdma_rfon_period_len_2, uint8_t tdma_rfon_period_len_3);
int rtw_pm_set_lps_dtim(_adapter *padapter, uint8_t lps_dtim);
uint8_t rtw_pm_get_lps_dtim(_adapter *padapter);
#endif  //__RTL871X_PWRCTRL_H_

