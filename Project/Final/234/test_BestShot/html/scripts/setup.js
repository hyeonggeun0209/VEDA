var MAX_CAMERA_NUM = 10;

window.onload = function() {
  // default tab 'Device'
  openDefaultTab();
  // addEventListener
  // initAddEventInputs();
};

function openDefaultTab() {
  document.querySelector('.tablinks.default-open').click();
}

function parseINIString(data){
  var regex = {
      section: /^\s*\[\s*([^\]]*)\s*\]\s*$/,
      param: /^\s*([^=]+?)\s*=\s*(.*?)\s*$/,
      comment: /^\s*;.*$/
  };
  var value = {};
  var lines = data.split(/[\r\n]+/);
  var section = null;
  lines.forEach(function(line){
      if(regex.comment.test(line)){
          return;
      }else if(regex.param.test(line)){
          var match = line.match(regex.param);
          if(section){
              value[section][match[1]] = match[2];
          }else{
              value[match[1]] = match[2];
          }
      }else if(regex.section.test(line)){
          var match = line.match(regex.section);
          value[match[1]] = {};
          section = match[1];
      }else if(line.length == 0 && section){
          section = null;
      };
  });
  return value;
}

async function get_ftp_def_setting(domObject) {
  let rootObject = domObject.parentElement.parentElement;
  const id = rootObject.querySelector('input[name="userid"]').value;
  const password = document.querySelector('input[name="password"]').value;
  let ftp_ip = document.getElementById('ftp-server').value;
  let ftp_port = document.getElementById('ftp-port').value;
  let ftp_id = document.getElementById('ftp-user-id').value;

  uri = `/stw-cgi/transfer.cgi?msubmenu=ftp&action=view`;
  var requestInit = {
    method: 'GET',
    credentials: forTest ? 'omit' : 'same-origin',
    headers: {
      'Content-Type': 'text/xml',
    },
  };

  try {
    resp = await fetch(uri, requestInit);
    var data = await resp.text();
    var ftp_config = parseINIString(data);
    // console.log(ftp_config);

    //set to textbox
    if(ftp_ip == "")
    {
      document.getElementById('ftp-server').value = ftp_config['Host'];
    }

    if(ftp_port == "")
    {
      document.getElementById('ftp-port').value = ftp_config['Port'];
    }

    if(ftp_id == "")
    {
      document.getElementById('ftp-user-id').value = ftp_config['Username'];
    }
  } catch (error) {
    console.log(error)
  }
  
}

function changeTab(domObject, evt, tabName) {
  var i, tabcontent, tablinks;

  tabcontent = document.getElementsByClassName("tabcontent");
  for (i = 0; i < tabcontent.length; i++) {
    tabcontent[i].style.display = "none";
  }

  //if ftp, get ftp default setting
  if (tabName === 'ftp'){
    get_ftp_def_setting(domObject);
  }
  tablinks = document.getElementsByClassName("tablinks");
  for (i = 0; i < tablinks.length; i++) {
    tablinks[i].className = tablinks[i].className.replace(" active", "");
  }

  document.querySelector("[data-id='" + tabName + "']").style.display = "block";
  evt.currentTarget.className += " active";
}

function changeAlarmOutDuration(e) {
  var alarmoutduration = document.getElementById("alarm-out-duration");
  var alarmoutmode = document.getElementById("alarm-out-mode");

  if(alarmoutduration.selectedOptions[0].value == 255)
  {
      alarmoutmode.value = "Over";
      alarmoutmode.disabled = true;
  }
  else
  { 
      alarmoutmode.disabled = false;
  }
}

function changeApplyAll(checked, parentName) {
  var selectorUserid = '#' + parentName + '-table tr[data-index]:not([data-index="1"]) [name="userid"]';
  var selectorPassword = '#' + parentName + '-table tr[data-index]:not([data-index="1"]) [name="password"]';
  var elems = document.querySelectorAll(selectorUserid + ', ' + selectorPassword);
  
  elems.forEach(function(el) {
    el.value = '';
    el.disabled = checked;
  });

  document.querySelectorAll(`#${parentName}-table tr[data-index]:not([data-index="1"]) [name="userid"]`).forEach(elem => elem.oninput(elem));
}

function checkRowAll(checked, parentName) {
  var exceptRowSelector = parentName === 'device' ? ':not([data-index="1"])' : '';
  var checkBoxes = document.querySelectorAll('#' + parentName + '-table tr[data-index]' + exceptRowSelector + ' [name="check"]');
  checkBoxes.forEach(function(el) {
    el.checked = checked;
  });

  // Delete 버튼 활성화(체크)/비활성화(언체크)
  disableDeleteBtn(!checked, parentName);
}

function checkRow(parentName) {
  var exceptRowSelector = parentName === 'device' ? ':not([data-index="1"])' : '';
  var checkBoxes = document.querySelectorAll('#' + parentName + '-table tr[data-index]' + exceptRowSelector + ' [name="check"]');
  var elCheckAll = document.querySelector('#' + parentName + '-check-all');

  var checkedCameraNum = 0;
  checkBoxes.forEach(function(el) {
    if (el.checked) {
      checkedCameraNum += 1;
    }
  });

  elCheckAll.checked = checkedCameraNum === checkBoxes.length;

  // 1개 이상의 카메라 선택했을 경우에만 Delete 버튼 활성화.
  if (checkedCameraNum > 0) {
    disableDeleteBtn(false, parentName);
  } else {
    disableDeleteBtn(true, parentName);
  }
}

function setInputFilter(textbox, inputFilter) {
  if (!textbox) {
    return;
  }
  ["input", "keydown", "keyup", "mousedown", "mouseup", "select", "contextmenu", "drop"].forEach(function (event) {
    textbox.addEventListener(event, function () {
      if (inputFilter(this.value)) {
        this.oldValue = this.value;
        this.oldSelectionStart = this.selectionStart;
        this.oldSelectionEnd = this.selectionEnd;
      } else if (this.hasOwnProperty("oldValue")) {
        this.value = this.oldValue;
        this.setSelectionRange(this.oldSelectionStart, this.oldSelectionEnd);
      } else {
        this.value = "";
      }
    });
  });
}

const emailAllowRegExp = /^[a-zA-Z0-9 ,\.\(\)\!:;~`/]*$/;
setInputFilter(document.querySelector('input[name="email-subject"]'), value => emailAllowRegExp.test(value));
setInputFilter(document.querySelector('input[name="email-msg"]'), value => emailAllowRegExp.test(value));

// document.getElementById('adminId').disabled = true;
setInputFilter(document.querySelector('input[name="rtspUser-Id"]'), value => /^[a-zA-Z0-9]*$/.test(value));
setInputFilter(document.querySelector('input[name="rtspUser-Password"]'), value => /^[a-zA-Z0-9-~`!@#$%^*()_\-\+=|{}\[\].?/]*$/.test(value));

function addRow(parentName, dataIndex) {
  var parent = document.querySelector('#' + parentName + '-table tbody');
  
  var rows = parent.querySelectorAll('tr[data-index]');
  var indexes = [];
  rows.forEach(function(row) {
    indexes.push(row.dataset.index);
  });

  // [only HTTP] index 없을 경우
  if (indexes.length === 0) {
    indexes.push(0);
  }

  var newIndex = Math.max.apply(Math, indexes) + 1;
  if( typeof dataIndex !=="undefined" ) {
    newIndex = dataIndex ;
  }
  // Device 탭의 경우 Master camera의 row를 복사 (삭제불가), 
  // HTTP 탭의 경우 모두 삭제 가능하므로 숨겨둔 Row를 복사 (.copy-row)
  var specialRowSelector = parentName === 'device' ? '[data-index="1"]' : '.copy-row';
  var originRow = parent.querySelector('tr' + specialRowSelector);
  var newRow = originRow.cloneNode(true);

  newRow.querySelector('.num').innerHTML = newIndex;
  newRow.dataset.index = newIndex;
  newRow.style.display = 'table-row';

  // Input 비우기
  newRow.querySelectorAll("input[type='text'], input[name='HTTPCommand']").forEach(function(el) {
    el.value = '';
  });
  
  // 
  // newRow.querySelectorAll("span[name='status']").forEach(function(el) {
  //   el.innerText = '';
  //   el.style.color = '';
  // });
  if( typeof dataIndex !=="undefined" && typeof rows[dataIndex-1] !== "undefined" ) {
    // rows[0].attributes["data-index"]
    rows[dataIndex-1].before(newRow);
  } else {
    parent.appendChild(newRow);
  }
  // Row 최대 8개 설정가능. 8개 이상일 시 Add 버튼 비활성화.
  if (newIndex === MAX_CAMERA_NUM) {
    disableAddBtn(true, parentName);
  }
  //setSettingData();
}

function deleteRow(parentName) {
  // 체크된 Row 삭제
  var checkedCheckBoxes = document.querySelectorAll('#' + parentName + '-table tr[data-index] [name="check"]:checked');
  checkedCheckBoxes.forEach(function(el) {
    var row = getParentByTagName(el, 'tr');
    var newIndex = row.attributes["data-index"].value;
    row.parentNode.removeChild(row);
    //addRow(parentName, newIndex);
  });

  // 인덱스 재설정 (data-index, .num(No.))
  var rows = document.querySelectorAll('#' + parentName + '-table tr[data-index]');
  Array.reduce.call(Array, rows, function(newIndex, row) {
    row.dataset.index = newIndex;
    row.querySelector('.num').innerHTML = newIndex === 1 && parentName === 'device' ? 'Master' : newIndex;

    return newIndex + 1;
  }, 1);

  // 8개 미만일 경우 Add 버튼 활성화
  if(rows.length < MAX_CAMERA_NUM) {
    disableAddBtn(false, parentName);
  }

  // Delete 버튼 비활성화 (체크된 Row 모두 삭제했으므로 무조건 비활성화 됨)
  disableDeleteBtn(true, parentName);
  // 전체 체크 해제
  document.querySelector('#' + parentName + '-check-all').checked = false;
  //checkDeviceListo4OptionOne();
  setSettingData();
}

function disableAddBtn(isDisable, parentName) {
  document.getElementById('btn-' + parentName + '-add').disabled = isDisable;
}

function disableDeleteBtn(isDisable, parentName) {
  document.getElementById('btn-' + parentName + '-delete').disabled = isDisable;
}

function changeTimeMode(mode) {
  console.log(mode);
  var h = document.getElementById('reset-time-h');
  var m = document.getElementById('reset-time-m');

  document.getElementById('reset-time-1').appendChild(mode === 'HM' ? h : m);
  document.getElementById('reset-time-2').appendChild(mode === 'HM' ? m : h);
}

function openHelp() {
  window.open('./help/index.html', '_blank', 'width=1200, height=900');
}

function openOpenSource() {
  window.open('./OpenSourceLicense_wama_ application_200624_EN.txt', '_blank', 'width=600, height=900');
}

function toggleAdvanced() {
  document.getElementById('btn-http-advanced').classList.toggle('active');
  document.getElementById('advanced').classList.toggle('show');
}

function checkRTSPID() {
  const dataCamera = document.querySelector('div[data-id="device"]');
  const masteruserid = dataCamera.querySelector('tr[data-index="1"] input[name="userid"]').value;
  
  if( masteruserid === document.getElementById('rtspUser-Id').value ) {
    alert("Admin ID is not allowed.");
    document.getElementById('rtspUser-Id').value = "";
  }
}