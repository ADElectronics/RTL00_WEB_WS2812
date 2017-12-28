/*
function openTab(evt, tabID)
{
	// Показываем выбранный контент
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) 
	{     
		if (tabcontent[i].id == tabID)
			tabcontent[i].style.display = "block";
		else
			tabcontent[i].style.display = "none";
    }   
	
	// Выделяем выбранную кнопку
	tablinks = document.getElementsByClassName("tablinks");
    for (i = 0; i < tablinks.length; i++) 
	{
        tablinks[i].className = tablinks[i].className.replace(" active", "");
    }   
    evt.currentTarget.className += " active";
}
*/
function openFilterSettings(chkbx)
{
	var i, content;
	content = document.getElementsByClassName("filtercontent");
	for (i = 0; i < content.length; i++) 
	{
        if (content[i].id == chkbx.id)
		{
			if(chkbx.checked == "1")
				content[i].style.display = "block";
			else
				content[i].style.display = "none";
		}
    }
	// chkbx.value = chkbx.checked ?
	sendFilterState(chkbx.name, chkbx.checked);
}

function changeOnOff(field)
{
    if (field.className === 'off')
    {
        sendFilterParam('ws_isenable', "1");
        field.src = 'on.gif';
        field.className = 'on';
    }
    else
    {
        sendFilterParam('ws_isenable', "0");
        field.src = 'off.gif';
        field.className = 'off';
    }
}

function setFormValues(form, cfg)
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
                openFilterSettings(field);
            }
            else if (field.type === 'image')
            {
                if (cfg[name] == '1')
                {
                    field.src = 'on.gif';
                    field.className = 'on';
                }
                else
                {
                    field.src = 'off.gif';
                    field.className = 'off';
                }
            }
            else
            {
                field.value = cfg[name];
            }
        }
    }
}

function sendFilterState(filtName, en) 
{
	var xhr = new XMLHttpRequest();
	var send = en === true ? '1' : '0';
	var params = filtName + '=' + encodeURIComponent(send);
	xhr.open("POST", '/index.html', true);
	xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
	xhr.onreadystatechange = function () 
	{
	    //if(xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200)
	    //console.log(xhr.responseText);
	};
	xhr.send(params);
}

function sendHSV(HSV)
{
    var xhr = new XMLHttpRequest();
    var hue = Math.round(255 * HSV.h);
    var sat = Math.round(255 * HSV.s);
    var val = Math.round(255 * HSV.v);

    var params = 'ws_filt_const_hue=' + encodeURIComponent(hue) +
                 '&ws_filt_const_sat=' + encodeURIComponent(sat) +
                 '&ws_filt_const_value=' + encodeURIComponent(val) +
                 '&ws_filt_const_update=' + encodeURIComponent('1');
    xhr.open("POST", '/index.html', true);
    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhr.onreadystatechange = function () {

    };
    xhr.send(params);
}

function loadHSV(picker, HSV)
{
    var hue = HSV.ws_filt_const_hue / 255;
    var sat = HSV.ws_filt_const_sat / 255;
    var val = HSV.ws_filt_const_value / 255;

    var rgb = hsvToRgb(hue, sat, val);
    var hex = '#' + byteToHex(rgb[0]) + byteToHex(rgb[1]) + byteToHex(rgb[2]);

    picker.setColorByHex(hex);
}

function byteToHex(d)
{
    var hex = d.toString(16);
    hex = "00".substr(0, 2 - hex.length) + hex;
    return hex;
}

function hsvToRgb(h, s, v) {
    var r, g, b;

    var i = Math.floor(h * 6);
    var f = h * 6 - i;
    var p = v * (1 - s);
    var q = v * (1 - f * s);
    var t = v * (1 - (1 - f) * s);

    switch (i % 6) {
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }

    return [Math.round(r * 255), Math.round(g * 255), Math.round(b * 255)];
}

function sendFilterParam(filtParam, val)
{
    var xhr = new XMLHttpRequest();
    var params = filtParam + '=' + encodeURIComponent(val);
    xhr.open("POST", '/index.html', true);
    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhr.onreadystatechange = function ()
    {

    };
    xhr.send(params);
}
