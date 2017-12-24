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
