const addToCart = productId => {
  // TODO 9.2
  // use addProductToCart(), available already from /public/js/utils.js
  // call updateProductAmount(productId) from this file
  console.log("jee");
  addProductToCart(productId);
  updateProductAmount(productId);
};

const decreaseCount = productId => {
  // TODO 9.2
  // Decrease the amount of products in the cart, /public/js/utils.js provides decreaseProductCount()
  // Remove product from cart if amount is 0,  /public/js/utils.js provides removeElement = (containerId, elementId
  const left = decreaseProductCount(productId);
  if (left === 0) {
    removeElement("cart-container", `product-${productId}`);}
  else updateProductAmount(productId);
};

const updateProductAmount = productId => {
  // TODO 9.2
  // - read the amount of products in the cart, /public/js/utils.js provides getProductCountFromCart(productId)
  // - change the amount of products shown in the right element's innerText
  document.getElementById(`amount-${productId}`).textContent = `${getProductCountFromCart(productId)}x`;

};

const placeOrder = async() => {
  // TODO 9.2
  // Get all products from the cart, /public/js/utils.js provides getAllProductsFromCart()
  // show the user a notification: /public/js/utils.js provides createNotification = (message, containerId, isSuccess = true)
  // for each of the products in the cart remove them, /public/js/utils.js provides removeElement(containerId, elementId)
  const cart = getAllProductsFromCart();
  cart.forEach(elem => {
    removeElement("cart-container", `product-${elem.id}`);
  });
  clearCart();
};

(async() => {
  // TODO 9.2
  // - get the 'cart-container' element
  // - use getJSON(url) to get the available products
  // - get all products from cart
  // - get the 'cart-item-template' template
  // - for each item in the cart
  //    * copy the item information to the template
  //    * hint: add the product's ID to the created element's as its ID to 
  //        enable editing ith 
  //    * remember to add event listeners for cart-minus-plus-button
  //        cart-minus-plus-button elements. querySelectorAll() can be used 
  //        to select all elements with each of those classes, then its 
  //        just up to finding the right index.  querySelectorAll() can be 
  //        used on the clone of "product in the cart" template to get its two
  //        elements with the "cart-minus-plus-button" class. Of the resulting
  //        element array, one item could be given the ID of 
  //        `plus-${product_id`, and other `minus-${product_id}`. At the same
  //        time we can attach the event listeners to these elements. Something 
  //        like the following will likely work:
  //          clone.querySelector('button').id = `add-to-cart-${prodouctId}`;
  //          clone.querySelector('button').addEventListener('click', () => addToCart(productId, productName));
  //
  // - in the end remember to append the modified cart item to the cart 

  const cartContainer = document.getElementById("cart-container");
  const itemTemplate = document.getElementById("cart-item-template");
  document.getElementById("place-order-button").addEventListener('click', placeOrder);
  const products = await getJSON('/api/products');
  const cart = Object.keys(window.sessionStorage);

  cart.forEach(inCart => {
    const product = products.find(product => product._id === inCart);
    const {_id: id, name, description, price } = product;

    const itemContainer = itemTemplate.content.cloneNode(true);
    itemContainer.querySelector('.item-row').id = `product-${id}`;
    const buttons = itemContainer.querySelectorAll('button');

    buttons[0].id = `plus-${id}`;
    buttons[1].id = `minus-${id}`;
    buttons[0].addEventListener('click', () => addToCart(id));
    buttons[1].addEventListener('click', () => decreaseCount(id));

    itemContainer.querySelectorAll('[class]').forEach(elem => {
      if(elem.classList.contains('cart-minus-plus-button')){
        return;
      }
      const prop = elem.className.split('-')[1];
      if (prop === "amount") {
        elem.id = `${prop}-${id}`;
      elem.textContent = `${getProductCountFromCart(id)}x`;
      }

      else if(!product[prop]) return;

      else{
        elem.id = `${prop}-${id}`;
        elem.textContent = product[prop];
      }


    });
    cartContainer.append(itemContainer);
    

  })
  

})();