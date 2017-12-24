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

function initWS2812Setting()
{
    var cfg =
    {
        ws_filt_rbw_enbl: "~ws_filt_rbw_enbl~",
        ws_filt_fd_enbl: "~ws_filt_fd_enbl~"
    }

    setFormValues(document.forms[0], cfg);
}
