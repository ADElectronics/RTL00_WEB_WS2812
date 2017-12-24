var setFormValues = function (form, cfg)
{
    var name, field;
    for (name in cfg)
    {
        if (form[name])
        {
            field = form[name];
            if (field[1] && field[1].type === 'checkbox')
            {
                field = field[1];
            }
            if (field.type === 'checkbox')
            {
                field.checked = cfg[name] === '1' ? true : false;
            }
            else
            {
                field.value = cfg[name];
            }
        }
    }
}

function initWiFiSetting()
{
    var cfg =
    {
        wifi_mode: "~wifi_cmode~",
        wifi_st_status: "~wifi_st_status~",
        wifi_ap_chl: "~wifi_ap_chl~",
        wifi_ap_auth: "~wifi_ap_auth~",
        wifi_bgn: "~wifi_bgn~",
        wifi_st_sleep: "~wifi_st_sleep~",
        wifi_st_auth: "~wifi_st_auth~",
        wifi_st_sbss: "~wifi_st_sbss~",
        wifi_ap_hssid: "~wifi_ap_hssid~",
        wifi_ap_dhcp: "~wifi_ap_dhcp~",
        wifi_txpow: "~wifi_txpow~",
        wifi_st_dhcp: "~wifi_st_dhcp~"
    }

    setFormValues(document.forms[0], cfg);
}
