    var logFlag=0;
    
    function login(){
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function(){
            if(this.readyState == 4 && this.status==200){
                document.getElementById("loginResponse").innerHTML = this.responseText;
                var buttons = document.getElementsByClassName("algo");
                for(let i=0;i<buttons.length;i++)
                {
                  buttons[i].removeAttribute("disabled");
                  buttons[i].removeAttribute("title");
                }
                logFlag=1;
            }
        };
        try{

            var email = document.getElementById("emailLogin").value;
            var pass = document.getElementById("passwordLogin").value;
            var data = "email="+encodeURIComponent(email) + "&pass="+encodeURIComponent(pass);
            xhr.open("POST","serwer/login.php",true);
            xhr.setRequestHeader("Content-Type","application/x-www-form-urlencoded") ;
            xhr.send(data);

        }
        catch(e){
            alert("Nie mozna polaczyc sie z serwerem")
        }

    }
    function register(){
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function(){
            if(this.readyState == 4 && this.status==200){
                document.getElementById("registerResponse").innerHTML = this.responseText;
            }
        };
        try{

            var email = document.getElementById("emailReg").value;
            var pass = document.getElementById("passwordReg").value;
            var data = "email="+encodeURIComponent(email) + "&pass="+encodeURIComponent(pass);
            xhr.open("POST","serwer/register.php",true);
            xhr.setRequestHeader("Content-Type","application/x-www-form-urlencoded") ;
            xhr.send(data);

        }
        catch(e){
            alert("Nie mozna polaczyc sie z serwerem")
        }

    }
    function isLogged(){
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function(){
          if(this.readyState == 4 && this.status==200){
            logFlag=this.responseText
          }
      };

      xhr.open("GET","serwer/isLogged.php",true);
      xhr.send();
    }

    function logout(){
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function(){
          if(this.readyState == 4 && this.status==200){
            document.getElementById("registerResponse").innerHTML= this.response;
            logFlag=0;
            location.reload();
          }
      };

      xhr.open("GET","serwer/logout.php",true);
      xhr.send();
    }

    function saveParams(flag) {
      if(logFlag!=0){
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {
        if(this.readyState == 4 && this.status == 200) {
          document.getElementById("save"+flag).innerHTML=this.responseText;
        }
      };

      switch(flag) {
        case 1:
          var speed = document.getElementById("speedInputBubble").value;
          var data = "speed="+encodeURIComponent(speed);
          xhr.open("POST","serwer/saveParams.php",true);
          xhr.send(data)
          break;
          case 2:
          var speed = document.getElementById("speedInputInsert").value;
          var data = "speed="+encodeURIComponent(speed);
          xhr.open("POST","serwer/saveParams.php",true);
          xhr.send(data)
          break;
          case 3:
          var speed = document.getElementById("speedInputSelecti").value;
          var data = "speed="+encodeURIComponent(speed);
          xhr.open("POST","serwer/saveParams.php",true);
          xhr.send(data)
          break;
          case 4:
          var speed = document.getElementById("speedInputMerge").value;
          var data = "speed="+encodeURIComponent(speed);
          xhr.open("POST","serwer/saveParams.php",true);
          xhr.send(data)
          break;
          case 5:
          var speed = document.getElementById("speedInputQuick").value;
          var data = "speed="+encodeURIComponent(speed);
          xhr.open("POST","serwer/saveParams.php",true);
          xhr.send(data)
          break;
          case 6:
          var speed = document.getElementById("speedInputHeap").value;
          var data = "speed="+encodeURIComponent(speed);
          xhr.open("POST","serwer/saveParams.php",true);
          xhr.send(data)
          break;
        default:
          break;
      }
      
      var data = "speed="+encodeURIComponent(speed);
      xhr.open("POST","serwer/saveParams.php",true);
      xhr.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
      xhr.send(data);
    }
    else {
      alert("Nie jestes zalogowany");
    }

    }

    function getAlgorithm(flag) {
      isLogged();
      if(logFlag == 1)
      {
      var xhr= new XMLHttpRequest();
      xhr.onreadystatechange = function() {
        if(this.readyState == 4 && this.status == 200) {
          document.getElementById("kod"+flag).innerHTML=this.responseText;
        }
      };
      var data="?flag="+flag;
      xhr.open("GET","serwer/getAlgorithm.php"+data,true);
      xhr.send(null);
    }
    else {
      alert("nie jesteś zalogowany");
    }
    }

    function hideAlgorithm(flag) {
      document.getElementById("kod"+flag).innerHTML="";
    }
    
    
    
    
    let barsArray = [];
    let context;
    let animationSpeed = [50,50,50,50,50,50];
    let isAnimating = false;

    // Funkcja do generowania losowych liczb całkowitych w danym zakresie
    function getRandomInt(min, max) {
      return Math.floor(Math.random() * (max - min + 1)) + min;
    }

    // Funkcja do rysowania słupków na kanvasie
    function drawBars(bars, currentIndex, keyIndex) {
      context.clearRect(0, 0, context.canvas.width, context.canvas.height);
      const barWidth = context.canvas.width / bars.length;

      bars.forEach((bar, index) => {
        const barHeight = (bar / Math.max(...bars)) * context.canvas.height;
        const x = index * barWidth;
        const y = context.canvas.height - barHeight;

        // Kolorowanie słupków na czerwono dla aktualnie porównywanego elementu
        // i zielono dla elementu o kluczu
        if (index === currentIndex) {
          context.fillStyle = "#e74c3c"; // Kolor czerwony dla aktualnie porównywanego elementu
        } else if (index === keyIndex) {
          context.fillStyle = "#2ecc71"; // Kolor zielony dla elementu o kluczu
        } else {
          context.fillStyle = "#3498db"; // Kolor nieaktywnych słupków
        }

        context.fillRect(x, y, barWidth, barHeight);

        context.strokeStyle = "#000"; // Kolor obramowania słupka
        context.strokeRect(x, y, barWidth, barHeight);
      });
    }

    function drawBarsQuick(leftIndex, rightIndex, pivotIndex) {
      context.clearRect(0, 0, context.canvas.width, context.canvas.height);
      const barWidth = context.canvas.width / barsArray[4].length;

      barsArray[4].forEach((bar, index) => {
        const barHeight = (bar / Math.max(...barsArray[4])) * context.canvas.height;
        const x = index * barWidth;
        const y = context.canvas.height - barHeight;

        if (index === pivotIndex) {
          context.fillStyle = "#e74c3c"; // Red color for pivot
        } else if (index >= leftIndex && index <= rightIndex) {
          context.fillStyle = "#2ecc71"; // Green color for pivot area
        } else {
          context.fillStyle = "#3498db"; // Blue color for other bars
        }

        context.fillRect(x, y, barWidth, barHeight);
        context.strokeStyle = "#000"; // Black border for bars
        context.strokeRect(x, y, barWidth, barHeight);
      });
    }

    // Algorytm sortowania bąbelkowego z animacją i licznikiem czasu
    async function bubbleSortWithAnimation() {
      const len = barsArray[0].length;
      let startTime = performance.now(); // Początkowy czas

      for (let i = 0; i < len - 1; i++) {
        for (let j = 0; j < len - 1 - i; j++) {
          // Rysowanie przed porównaniem
          drawBars(barsArray[0], j, j + 1);
          await new Promise(resolve => setTimeout(resolve, 101-animationSpeed[0]));

          if (barsArray[0][j] > barsArray[0][j + 1]) {
            // Zamiana miejscami, gdy elementy są w złej kolejności
            const temp = barsArray[0][j];
            barsArray[0][j] = barsArray[0][j + 1];
            barsArray[0][j + 1] = temp;

            // Rysowanie po zamianie
            drawBars(barsArray[0], j, j + 1);
            // Opóźnienie animacji
            await new Promise(resolve => setTimeout(resolve, 101-animationSpeed[0]));
          }
        }
      }

      let endTime = performance.now(); // Końcowy czas
      let elapsedTime = (endTime - startTime) / 1000; // Czas wykonania w sekundach

      // Aktualizacja tekstu z czasem wykonania
      document.getElementById("timerBubble").textContent = `Czas: ${elapsedTime.toFixed(2)} sekund`;
      isAnimating = false;
    }

    async function insertionSortWithAnimation() {
      const len = barsArray[1].length;
      let startTime = performance.now(); // Początkowy czas

      for (let i = 1; i < len; i++) {
        let key = barsArray[1][i];
        let j = i - 1;

        while (j >= 0 && barsArray[1][j] > key) {
          // Rysowanie przed porównaniem
          drawBars(barsArray[1], j + 1, j);
          await new Promise(resolve => setTimeout(resolve, 101-animationSpeed[1]));

          // Przesuwanie elementów większych niż klucz
          barsArray[1][j + 1] = barsArray[1][j];

          // Rysowanie po przesunięciu
          drawBars(barsArray[1], j + 1, j);
          // Opóźnienie animacji
          await new Promise(resolve => setTimeout(resolve, 101-animationSpeed[1]));

          j--;
        }

        // Wstawienie klucza na właściwe miejsce
        barsArray[1][j + 1] = key;

        // Rysowanie po wstawieniu
        drawBars(barsArray[1], j + 1, -1);
        // Opóźnienie animacji
        await new Promise(resolve => setTimeout(resolve, 101-animationSpeed[1]));
      }

      let endTime = performance.now(); // Końcowy czas
      let elapsedTime = (endTime - startTime) / 1000; // Czas wykonania w sekundach

      // Aktualizacja tekstu z czasem wykonania
      document.getElementById("timerInsert").textContent = `czas: ${elapsedTime.toFixed(2)} sekund`;
      isAnimating = false;
    }
    // Algorytm sortowania przez wybieranie z animacją i licznikiem czasu
    async function selectionSortWithAnimation() {
      const len = barsArray[2].length;
      let startTime = performance.now(); // Początkowy czas

      for (let i = 0; i < len - 1; i++) {
        let minIndex = i;

        for (let j = i + 1; j < len; j++) {
          // Rysowanie przed porównaniem
          drawBars(barsArray[2], j, minIndex);
          await new Promise(resolve => setTimeout(resolve, 101-animationSpeed[2]));

          if (barsArray[2][j] < barsArray[2][minIndex]) {
            minIndex = j;
          }
        }

        // Zamiana miejscami minimalnego elementu z aktualnym
        const temp = barsArray[2][i];
        barsArray[2][i] = barsArray[2][minIndex];
        barsArray[2][minIndex] = temp;

        // Rysowanie po zamianie
        drawBars(barsArray[2], i, minIndex);
        // Opóźnienie animacji
        await new Promise(resolve => setTimeout(resolve, 101-animationSpeed[2]));
      }

      let endTime = performance.now(); // Końcowy czas
      let elapsedTime = (endTime - startTime) / 1000; // Czas wykonania w sekundach

      // Aktualizacja tekstu z czasem wykonania
      document.getElementById("timerSelection").textContent = `Czas: ${elapsedTime.toFixed(2)} sekund`;
      isAnimating = false;
    }

    // Algorytm sortowania przez scalanie z animacją i licznikiem czasu
    async function mergeSortWithAnimation(left, right) {
      if (left < right) {
        const mid = Math.floor((left + right) / 2);

        // Rekurencyjne sortowanie lewej i prawej części
        await mergeSortWithAnimation(left, mid);
        await mergeSortWithAnimation(mid + 1, right);

        // Scalanie dwóch posortowanych części
        await merge(left, mid, right);
      }
    }

    async function merge(left, mid, right) {
      const n1 = mid - left + 1;
      const n2 = right - mid;

      const leftArray = new Array(n1);
      const rightArray = new Array(n2);

      // Kopiowanie danych do tymczasowych tablic
      for (let i = 0; i < n1; i++) {
        leftArray[i] = barsArray[3][left + i];
      }
      for (let j = 0; j < n2; j++) {
        rightArray[j] = barsArray[3][mid + 1 + j];
      }

      let i = 0, j = 0, k = left;

      // Porównywanie i scalanie elementów
      while (i < n1 && j < n2) {
        // Rysowanie przed porównaniem
        drawBars(barsArray[3], left + i, mid + j, true);
        await new Promise(resolve => setTimeout(resolve, 101-animationSpeed[3]));

        if (leftArray[i] <= rightArray[j]) {
          barsArray[3][k] = leftArray[i];
          i++;
        } else {
          barsArray[3][k] = rightArray[j];
          j++;
        }

        // Rysowanie po scaleniu
        drawBars(barsArray[3], left + i, mid + j, false);
        await new Promise(resolve => setTimeout(resolve, 101-animationSpeed[3]));

        k++;
      }

      // Kopiowanie pozostałych elementów z lewej tablicy
      while (i < n1) {
        barsArray[3][k] = leftArray[i];
        k++;
        i++;
      }

      // Kopiowanie pozostałych elementów z prawej tablicy
      while (j < n2) {
        barsArray[3][k] = rightArray[j];
        k++;
        j++;
      }
    }

    function swap(arr, i, j) {
      const temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }

    async function quickSortWithAnimation(low, high) {
      if (low < high) {
        const pivotIndex = await partition(low, high);
        await Promise.all([
          quickSortWithAnimation(low, pivotIndex - 1),
          quickSortWithAnimation(pivotIndex + 1, high)
        ]);
      }
    }

    async function partition(low, high) {
      const pivot = barsArray[4][high];
      let left = low;
      let right = high - 1;

      while (true) {
        while (left <= right && barsArray[4][left] < pivot) {
          left++;
        }

        while (left <= right && barsArray[4][right] > pivot) {
          right--;
        }

        if (left < right) {
          swap(barsArray[4], left, right);
        } else {
          break;
        }

        drawBarsQuick(left, right, high);
        await new Promise(resolve => setTimeout(resolve, 101-animationSpeed[4]));
      }

      swap(barsArray[4], left, high);
      drawBarsQuick(left, right, left);
      await new Promise(resolve => setTimeout(resolve, 101-animationSpeed[4]));

      return left;
    }

    async function heapSortWithAnimation() {
      const heapSize = barsArray[5].length;

      // Budowanie kopca
      for (let i = Math.floor(heapSize / 2) - 1; i >= 0; i--) {
        await heapify(heapSize, i);
      }

      // Wyjmowanie elementów z kopca
      for (let i = heapSize - 1; i > 0; i--) {
        // Zamiana miejscami korzenia z ostatnim elementem
        const temp = barsArray[5][0];
        barsArray[5][0] = barsArray[5][i];
        barsArray[5][i] = temp;

        // Rysowanie po zamianie
        drawBars(barsArray[5], i - 1, 0);
        // Opóźnienie animacji
        await new Promise(resolve => setTimeout(resolve, 101-animationSpeed[5]));

        // Naprawa kopca dla pozostałych elementów
        await heapify(i, 0);
      }

      isAnimating = false;
    }

    // Funkcja naprawiająca kopiec
    async function heapify(heapSize, rootIndex) {
      let largest = rootIndex;
      const leftChild = 2 * rootIndex + 1;
      const rightChild = 2 * rootIndex + 2;

      if (leftChild < heapSize && barsArray[5][leftChild] > barsArray[5][largest]) {
        largest = leftChild;
      }

      if (rightChild < heapSize && barsArray[5][rightChild] > barsArray[5][largest]) {
        largest = rightChild;
      }

      if (largest !== rootIndex) {
        // Zamiana miejscami korzenia z największym elementem
        const temp = barsArray[5][rootIndex];
        barsArray[5][rootIndex] = barsArray[5][largest];
        barsArray[5][largest] = temp;

        // Rysowanie po zamianie
        drawBars(barsArray[5], heapSize, rootIndex);
        // Opóźnienie animacji
        await new Promise(resolve => setTimeout(resolve, 101-animationSpeed[5]));

        // Rekurencyjne naprawianie kopca dla elementów pod korzeniem
        await heapify(heapSize, largest);
      }
    }

    // Funkcja do rozpoczęcia animacji
    async function startAnimationHeap() {
      if (!isAnimating) {
        isAnimating = true;
        canvas = document.getElementById('heapSortCanvas');
        context = canvas.getContext('2d');
        let startTime = performance.now(); // Początkowy czas
        await heapSortWithAnimation();

        let endTime = performance.now(); // Końcowy czas
        let elapsedTime = (endTime - startTime) / 1000; // Czas wykonania w sekundach

        // Aktualizacja tekstu z czasem wykonania
        document.getElementById("timerHeap").textContent = `Czas: ${elapsedTime.toFixed(2)} sekund`;
        isAnimating = false;
      }
    }

    function startAnimationQuick() {
      if (!isAnimating) {
        isAnimating = true;
        canvas = document.getElementById('quickSortCanvas');
        context = canvas.getContext('2d');
        const startTime = performance.now();
        quickSortWithAnimation(0, barsArray[4].length - 1).then(() => {
          isAnimating = false;
          const endTime = performance.now();
          const elapsedTime = ((endTime - startTime) / 1000).toFixed(2); // Convert to seconds
          document.getElementById("timerQuick").textContent = `Czas: ${elapsedTime} sekund`;
        });
      }
    }

    // Funkcja do rozpoczęcia animacji
    async function startAnimationMerge() {
      if (!isAnimating) {
        isAnimating = true;
        canvas = document.getElementById('mergeSortCanvas');
        context = canvas.getContext('2d');
        const len = barsArray[3].length - 1;
        let startTime = performance.now(); // Początkowy czas

        await mergeSortWithAnimation(0, len);

        let endTime = performance.now(); // Końcowy czas
        let elapsedTime = (endTime - startTime) / 1000; // Czas wykonania w sekundach

        // Aktualizacja tekstu z czasem wykonania
        document.getElementById("timerMerge").textContent = `Czas: ${elapsedTime.toFixed(2)} sekund`;
        isAnimating = false;
      }
    }

    // Funkcja do rozpoczęcia animacji
    function startAnimationSelection() {
      if (!isAnimating) {
        isAnimating = true;
        canvas = document.getElementById('selectionSortCanvas');
        context = canvas.getContext('2d');
        selectionSortWithAnimation();
      }
    }

    // Funkcja do rozpoczęcia animacji
    function startAnimationInsert() {
      if (!isAnimating) {
        isAnimating = true;
        canvas = document.getElementById('insertionSortCanvas');
        context = canvas.getContext('2d');
        insertionSortWithAnimation();
      }
    }

    // Funkcja do rozpoczęcia animacji
    function startAnimationBubble() {
      if (!isAnimating) {
        isAnimating = true;
        canvas = document.getElementById('bubbleSortCanvas');
        context = canvas.getContext('2d');
        bubbleSortWithAnimation();
      }
    }

    // Funkcja do generowania nowych losowych liczb i rozpoczęcia animacji
    function generateNewNumbers(flag) {
      barsArray[flag-1] = Array.from({ length: barsArray[flag-1].length }, () => getRandomInt(10, 200));

      switch(flag)
      {
        case 1:
          canvas = document.getElementById('bubbleSortCanvas');
          context = canvas.getContext('2d');
          document.getElementById("timerBubble").textContent = "Czas: 0 sekund";
          break;
        case 2:
          canvas = document.getElementById('insertionSortCanvas');
          context = canvas.getContext('2d');
          document.getElementById("timerInsert").textContent = "Czas: 0 sekund";
          break;
        case 3:
          canvas = document.getElementById('selectionSortCanvas');
          context = canvas.getContext('2d');
          document.getElementById("timerSelection").textContent = "Czas: 0 sekund";
          break;
        case 4:
          canvas = document.getElementById('mergeSortCanvas');
          context = canvas.getContext('2d');
          document.getElementById("timerMerge").textContent = "Czas: 0 sekund";
          break;
        case 5:
          canvas = document.getElementById('quickSortCanvas');
          context = canvas.getContext('2d');
          document.getElementById("timerQuick").textContent = "Czas: 0 sekund";
          break;
        case 6:
          canvas = document.getElementById('heapSortCanvas');
          context = canvas.getContext('2d');
          document.getElementById("timerHeap").textContent = "Czas: 0 sekund";
          break;
        default:
          break;
      }
      drawBars(barsArray[flag-1]);
      
    }

    // Funkcja do aktualizacji szybkości animacji podczas przesuwania suwaka
    function updateSpeed(flag) {
      switch(flag)
      {
        case 1:
          animationSpeed[0] = document.getElementById('speedInputBubble').value;
          document.getElementById("speedValueBubble").innerHTML=animationSpeed[0];
          break;
        case 2:
          animationSpeed[1] = document.getElementById('speedInputInsert').value;
          document.getElementById("speedValueInsert").innerHTML=animationSpeed[1];
          break;
        case 3:
          animationSpeed[2] = document.getElementById('speedInputSelect').value;
          document.getElementById("speedValueSelect").innerHTML=animationSpeed[2];
          break;
        case 4:
          animationSpeed[3] = document.getElementById('speedInputMerge').value;
          document.getElementById("speedValueMerge").innerHTML=animationSpeed[3];
          break;
        case 5:
          animationSpeed[4] = document.getElementById('speedInputQuick').value;
          document.getElementById("speedValueQuick").innerHTML=animationSpeed[4];
          break;
        case 6:
          animationSpeed[5] = document.getElementById('speedInputHeap').value;
          document.getElementById("speedValueHeap").innerHTML=animationSpeed[5];
          break;
        default:
          break;
      }
    }

    // Inicjalizacja
    canvas = document.getElementById('bubbleSortCanvas');
    context = canvas.getContext('2d');
    const numBars = 30; // Liczba słupków

    barsArray[0] = Array.from({ length: numBars }, () => getRandomInt(10, 200));

    // Rysowanie początkowego stanu słupków
    drawBars(barsArray[0]);

    canvas = document.getElementById('insertionSortCanvas');
    context = canvas.getContext('2d');
    barsArray[1] = Array.from({ length: numBars }, () => getRandomInt(10, 200));
    drawBars(barsArray[1]);

    canvas = document.getElementById('selectionSortCanvas');
    context = canvas.getContext('2d');
    barsArray[2] = Array.from({ length: numBars }, () => getRandomInt(10, 200));
    drawBars(barsArray[2]);

    canvas = document.getElementById('mergeSortCanvas');
    context = canvas.getContext('2d');
    barsArray[3] = Array.from({ length: numBars }, () => getRandomInt(10, 200));
    drawBars(barsArray[3]);

    canvas = document.getElementById('quickSortCanvas');
    context = canvas.getContext('2d');
    barsArray[4] = Array.from({ length: numBars }, () => getRandomInt(10, 200));
    drawBars(barsArray[4]);

    canvas = document.getElementById('heapSortCanvas');
    context = canvas.getContext('2d');
    barsArray[5] = Array.from({ length: numBars }, () => getRandomInt(10, 200));
    drawBars(barsArray[5],-1,-1);