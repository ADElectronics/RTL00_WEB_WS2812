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

function initSystemSetting()
{
    var cfg =
    {
        cfg_sleep: "~cfg_sleep~",
        cfg_debug: "~cfg_debug~",
        cfg_web_twd: "~cfg_web_twd~",
        cfg_pinclr: "~cfg_pinclr~",
        cfg_netbios: "~cfg_netbios~",
        cfg_sntp: "~cfg_sntp~",
        cfg_cdns: "~cfg_cdns~",
        cfg_mdb_reop: "~cfg_mdb_reop~"
    }

    setFormValues(document.forms[0], cfg);
}
