const digestClient = new DigestFetch('admin', '5dnpqxla!!', { algorithm: 'SHA256' });
const forTest = false;
const testHost = 'http://192.168.124.180';
const testHostName = '192.168.124.180';
const testPort = '80';
const imageMaxSize = 300 * 1024;
const MaxDevCount = 9;
let EnableBestShot = false;
let abortController;

function xmlToJson(xml) {
  // Create the return object
  var obj = {};

  if (!xml) {
    return obj;
  }

  if (xml.nodeType == 1) { // element
    // do attributes
    if (xml.attributes.length > 0) {
      obj["@attributes"] = {};
      for (var j = 0; j < xml.attributes.length; j++) {
        var attribute = xml.attributes.item(j);
        obj["@attributes"][attribute.nodeName] = attribute.nodeValue;
      }
    }
  } else if (xml.nodeType == 3) { // text
    obj = xml.nodeValue;
  }

  // do children
  // If just one text node inside
  if (xml.hasChildNodes() && xml.childNodes.length === 1 && xml.childNodes[0].nodeType === 3) {
    if (obj["@attributes"]) {
      obj["value"] = xml.childNodes[0].nodeValue
    } else {
      obj = xml.childNodes[0].nodeValue;
    }
  } else if (xml.hasChildNodes()) {
    for (var i = 0; i < xml.childNodes.length; i++) {
      var item = xml.childNodes.item(i);
      var nodeName = item.nodeName;
      if (typeof (obj[nodeName]) == "undefined") {
        obj[nodeName] = xmlToJson(item);
      } else {
        if (typeof (obj[nodeName].push) == "undefined") {
          var old = obj[nodeName];
          obj[nodeName] = [];
          obj[nodeName].push(old);
        }
        obj[nodeName].push(xmlToJson(item));
      }
    }
  }
  return obj;
}

const convertField = (() => {
  const map = new Map();

  const toJson = obj => typeof obj === 'string' ? JSON.parse(obj) : {};
  const toBoolean = value => value === 'true';

  ['imageTransfer'].forEach(field => map.set(field, toJson));
  ['enable', 'base64ObjectImage'].forEach(field => map.set(field, toBoolean));
  return (key, value) => {
    const convertFunc = map.get(key);
    if (convertFunc) {
      return convertFunc(value);
    } else {
      return value;
    }
  };
})();
 
async function getFetch(uri){
  abortController = new AbortController();
  const signal = abortController.signal;
  var requestInit = {
    method: 'GET',
    credentials: forTest ? 'omit' : 'same-origin',
    headers: {
      'Content-Type': 'text/plain',
    },
    signal: signal
  };
  var resp;
  try {
    if(forTest) {
      var hostURL = ( testPort !== '' ? (testHost + ":" + testPort) : testHost ) ;
      resp = await digestClient.fetch(hostURL + uri, requestInit);
    } else {
      resp = await fetch(uri, requestInit);
    }
    return await resp;
  } catch (error) {
    console.error(error);
  }
}

async function postFetch(uri, bodyData){
  var requestInit = {
    method: 'POST',
    credentials: forTest ? 'omit' : 'same-origin',
    headers: {
      'Content-Type': 'text/xml',
    },
    body: bodyData,
  };
  var resp;
  try {
    if(forTest) {
      var hostURL = ( testPort !== '' ? (testHost + ":" + testPort) : testHost ) ;
      resp = await digestClient.fetch(hostURL + uri, requestInit);
    } else {
      resp = await fetch(uri, requestInit);
    }
    return await resp.text();
  } catch (error) {
    console.error(error);
  }
}

async function putFetch(uri, bodyData){
  console.log(bodyData);
  var requestInit = {
    method: 'PUT',
    credentials: forTest ? 'omit' : 'same-origin',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify(bodyData),
  };
  var resp;
  try {
    if(forTest) {
      var hostURL = ( testPort !== '' ? (testHost + ":" + testPort) : testHost ) ;
      resp = await digestClient.fetch(hostURL + uri, requestInit);
    } else {
      resp = await fetch(uri, requestInit);
    }
    return await resp.text();
  } catch (error) {
    console.error(error);
  }
}

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

async function sendRequest(id, password, url) {
  var requestInit = {
    credentials: forTest ? 'omit' : 'same-origin',
  };
  return new Promise(async (resolve, reject) => {
    try {
      let client = new DigestFetch(id, password);
      let resp = await client.fetch(url, requestInit);
      if (resp.status === 200) {
        resolve(await resp.text());
      } else if (resp.status === 401) {
        // client = new DigestFetch(id, password, { algorithm: 'MD5' });
        client = new DigestFetch(id, password, { algorithm: 'SHA256' });
        resp = await client.fetch(url, requestInit);
        if (resp.status === 200) {
          resolve(await resp.text());
        } else {
          reject(resp.status);
        }
      } else {
        reject(resp.status);
      }
    } catch (error) {
      console.log(error);
      reject(error);
    }
  });
}

function fill_facedata(Element, row)
{
  const humanFace = Element.getElementsByTagName("tt:HumanFace")[0];
  let attributes = [];
  if (humanFace) {
    const gender = humanFace.getElementsByTagName("fc:Gender")[0].textContent;
    const ageType = humanFace.getElementsByTagName("fc:AgeType")[0].textContent;
    const opticals = humanFace.getElementsByTagName("fc:Opticals")[0].getElementsByTagName("fc:Wear")[0].textContent;
    const mask = humanFace.getElementsByTagName("fc:Mask")[0].getElementsByTagName("fc:Wear")[0].textContent;
    const hat = humanFace.getElementsByTagName("fc:Hat")[0].getElementsByTagName("fc:Wear")[0].textContent;

    if (gender) attributes.push(gender);
    if (ageType) attributes.push(ageType);
    if (opticals === "true") attributes.push("Glasses");
    if (mask === "true") attributes.push("Mask");
    if (hat === "true") attributes.push("Hat");
  }

  const attributeCell = document.createElement("td");
  attributeCell.textContent = attributes.join(", ");
  row.appendChild(attributeCell);
}

function fill_humandata(Element, row)
{
  const humanBody = Element.getElementsByTagName("tt:HumanBody")[0];
  let attributes = [];
  if (humanBody) {
    const gender = humanBody.getElementsByTagName("bd:Gender")[0].textContent;
    const hat = humanBody.getElementsByTagName("bd:Hat")[0].getElementsByTagName("bd:Wear")[0].textContent;

    const tops = humanBody.getElementsByTagName("bd:Tops")[0];
    const topsColors = tops.getElementsByTagName("bd:Color")[0];
    const topLength = tops.getElementsByTagName("bd:Length")[0]?.textContent || "";
    
    let topColorStrings = [];
    const topColorClusters = topsColors.getElementsByTagName("tt:ColorCluster");
    for (let j = 0; j < topColorClusters.length; j++) {
        topColorStrings.push(topColorClusters[j].getElementsByTagName("tt:ColorString")[0].textContent);
    }

    const topsInfo = topColorStrings.length > 0 ? `shirt(${topColorStrings.join(", ")}, ${topLength})` : "";

    const bottoms = humanBody.getElementsByTagName("bd:Bottoms")[0];
    const bottomsColors = bottoms.getElementsByTagName("bd:Color")[0];
    const bottomLength = bottoms.getElementsByTagName("bd:Length")[0]?.textContent || "";
    
    let bottomColorStrings = [];
    const bottomColorClusters = bottomsColors.getElementsByTagName("tt:ColorCluster");
    for (let j = 0; j < bottomColorClusters.length; j++) {
        bottomColorStrings.push(bottomColorClusters[j].getElementsByTagName("tt:ColorString")[0].textContent);
    }

    const bottomsInfo = topColorStrings.length > 0 ? `Trousers(${bottomColorStrings.join(", ")}, ${bottomLength})` : "";

    const Bag = humanBody.getElementsByTagName("bd:Bag")[0];
    let BagContent;
    if(Bag)
    {
      BagContent = Bag.getElementsByTagName("bd:Category")[0].textContent;
    }

    if (gender) attributes.push(gender);
    if (BagContent) attributes.push(BagContent);
    if (hat === "true") attributes.push("Hat");
    if(topsInfo != "") attributes.push(topsInfo);
    if(bottomsInfo != "") attributes.push(topsInfo);
  }

  const attributeCell = document.createElement("td");
  attributeCell.textContent = attributes.join(", ");
  row.appendChild(attributeCell);
}

function fill_VehicleData(Element, row)
{
  const Vehicle = Element.getElementsByTagName("tt:VehicleInfo")[0];
  let attributes = [];
  if (Vehicle) {
    const Type = Vehicle.getElementsByTagName("tt:Type")[0].textContent;

    const Color = Vehicle.getElementsByTagName("tt:Color")[0];
    
    let ColorStrings = [];
    const ColorClusters = Color.getElementsByTagName("tt:ColorCluster");
    for (let j = 0; j < ColorClusters.length; j++) {
      ColorStrings.push(ColorClusters[j].getElementsByTagName("tt:ColorString")[0].textContent);
    }
    const ColorInfo = ColorStrings.length > 0 ? `Color(${ColorStrings.join(", ")})` : "";

    if(Type) attributes.push(Type);
    if(ColorInfo != "") attributes.push(ColorInfo);
  }

  const attributeCell = document.createElement("td");
  attributeCell.textContent = attributes.join(", ");
  row.appendChild(attributeCell);
}

async function parse_metadata(metadata)
{
  const parser = new DOMParser();
  const xmlDoc = parser.parseFromString(metadata, "text/xml");

  const objects = xmlDoc.getElementsByTagName("tt:Object");

  for (let i = 0; i < objects.length; i++) {
    const imageRefNode = objects[i].getElementsByTagName("tt:ImageRef")[0];
    if (imageRefNode) {
      const imageRef = objects[i].getElementsByTagName("tt:ImageRef")[0];
      const imagePath = imageRef ? imageRef.textContent : "";
      const tableBody = document.getElementById("table-body");
      const row = document.createElement("tr");

      const classCandidate = objects[i].getElementsByTagName("tt:ClassCandidate")[0];
      const type = classCandidate ? classCandidate.getElementsByTagName("tt:Type")[0].textContent : "N/A";

      const typeCell = document.createElement("td");
      typeCell.textContent = type;
      row.appendChild(typeCell);

      if(type == "Face")
      {
        fill_facedata(objects[i], row);
      }
      else if(type == "Human")
      {
        fill_humandata(objects[i], row);
      }
      // else if(type == "LicensePlate")
      // {

      // }
      else if(type == "Vehical")
      {
        fill_VehicleData(objects[i], row);
      }
      else
      {
        const attributeCell = document.createElement("td");
        row.appendChild(attributeCell);
      }
      
      fetch(imagePath)
      .then(response => {
          if (!response.ok) {
              throw new Error('Network response was not ok ' + response.statusText);
          }
          const imgElement = document.createElement('img');
          imgElement.src = imagePath;
          imgElement.alt = "Image";
          imgElement.style.width = "250px";
          imgElement.style.height = "138px";
          const attributeCell = document.createElement("td");
          attributeCell.appendChild(imgElement);
          row.appendChild(attributeCell);
          tableBody.appendChild(row);
      })
      .catch(error => {
          console.error('There was a problem with the fetch operation:', error);
      });
    }
  }
}

function getData(Response)
{
  const filePathRegex = /download\/test_BestShot\/[^\s]+/;
  const match = Response.match(filePathRegex);

  if (match && match[0]) {
    let filePath = match[0];
    filePath = '/' + filePath;
    // console.log("file path:", filePath);

    fetch(filePath)
      .then(response => {
          if (!response.ok) {
              throw new Error(`HTTP error! status: ${response.status}`);
          }
          return response.text();
      })
      .then(data => {
          // console.log("file data:", data);
          parse_metadata(data);
      })
      .catch(error => {
          console.error("error when read file:", error);
      });
  }
}

async function fetchStreamData() {
  const url = '/stw-cgi/openapp.cgi?AppID=test_BestShot&action=monitor';
  const StopUrl = '/stw-cgi/openapp.cgi?AppID=test_BestShot&msubmenu=StopMonitor';
  EnableBestShot = true;
  try {
    do
    {
      await getFetch(StopUrl);

      const response = await getFetch(url);

      if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status}`);
      }

      const reader = response.body.getReader();
      const decoder = new TextDecoder();

      let done = false;
      while (!done && EnableBestShot) {
          const { value, done: readerDone } = await reader.read();
          done = readerDone;

          if (value) {
              const chunk = decoder.decode(value, { stream: true });
              console.log(chunk);
              getData(chunk);
              //document.getElementById("data").innerHTML += `<p>${chunk}</p>`;
          }
          console.log(done);
      }
    } while(EnableBestShot)
  } catch (error) {
      console.error("Error fetching data:", error);
  }
  if (abortController) {
    abortController.abort();
    await getFetch(StopUrl);
    console.log('Fetch aborted.');
  }
}

async function StopStreamData() {
  EnableBestShot = false;
}

async function getBestShotConfig() {
  const isEnable = document.getElementById('isEnable');
  const Face = document.getElementById('Face');
  const Person = document.getElementById('Person');
  const LicensePlate = document.getElementById('LicensePlate');
  const Vehicle = document.getElementById('Vehicle');
  const base64ObjectImage = document.getElementById('base64ObjectImage');
  const StartGetBetShot = document.getElementById('StartGetBetShot');
  const StopGetBetShot = document.getElementById('StopGetBetShot');

  const url = '/opensdk/WiseAI/configuration/imagetransfer';
  fetch(url)
  const response = await getFetch(url);
  const data = await response.json();
  const objectTypes = data.imageTransfer[0].objectTypes;

  isEnable.checked = data.imageTransfer[0].enable ;
  base64ObjectImage.checked = data.imageTransfer[0].base64ObjectImage;
  Face.checked  = objectTypes.includes("Face");
  Person.checked  = objectTypes.includes("Person");
  LicensePlate.checked  = objectTypes.includes("LicensePlate");
  Vehicle.checked  = objectTypes.includes("Vehicle");

  if(isEnable.checked == true)
  {
    Face.disabled = false;
    Person.disabled = false;
    LicensePlate.disabled = false;
    Vehicle.disabled = false;
    base64ObjectImage.disabled = false;
    StartGetBetShot.disabled = false;
    StopGetBetShot.disabled = false;
  }
  else
  {
    Face.disabled = true;
    Person.disabled = true;
    LicensePlate.disabled = true;
    Vehicle.disabled = true;
    base64ObjectImage.disabled = true;
    StartGetBetShot.disabled = true;
    StopGetBetShot.disabled = true;
  }
}

async function SetBestShotConfig() {
  const isEnable = document.getElementById('isEnable').checked;
  const base64ObjectImage = document.getElementById('base64ObjectImage').checked;

  const objectTypes = [];
  if (document.getElementById('Person').checked) objectTypes.push('Person');
  if (document.getElementById('Vehicle').checked) objectTypes.push('Vehicle');
  if (document.getElementById('Face').checked) objectTypes.push('Face');
  if (document.getElementById('LicensePlate').checked) objectTypes.push('LicensePlate');

  const payload = {
    channel: 0,
    enable: isEnable,
    objectTypes: objectTypes,
    base64ObjectImage: base64ObjectImage,
  };

  const url = '/opensdk/WiseAI/configuration/imagetransfer';
  const response = await putFetch(url,payload);

  if(!response.includes("Success"))
  {
    alert("FAILED");
  }
  else
  {
    alert("SUCCESS");
  }
}