

const addToCart = (productId, productName) => {
  // TODO 9.2
  // you can use addProductToCart(), available already from /public/js/utils.js
  // for showing a notification of the product's creation, /public/js/utils.js  includes createNotification() function
  const count = addProductToCart(productId);
  createNotification(`Added ${productName} to cart!`, 'notifications-container');
};



(async() => {
  //TODO 9.2 
  // - get the 'products-container' element from the /products.html
  // - get the 'product-template' element from the /products.html
  // - save the response from await getJSON(url) to get all the products. 
  //      getJSON(url) is available to this script in products.html, as "js/utils.js" script has been added to 
  //      products.html before this script file 
  // - then, loop throug the products in the response, and for each of the products:
  //    * clone the template
  //    * add product information to the template clone
  //    * remember to add an event listener for the button's 'click' event, and call addToCart() in the event listener's callback
  // - remember to add the products to the the page

const productsContainer = document.querySelector('#products-container');
const productTemplate = document.querySelector('#product-template');
const products = await getJSON('/api/products');

products.forEach(product => {
  const { _id: id, name, description, price } = product;
  const prodContrainer = productTemplate.content.cloneNode(true);
  
  prodContrainer.querySelector('.item-row').id = `product-${id}`;
  prodContrainer.querySelector('button').id = `add-to-cart-${id}`
  prodContrainer.querySelector('button').addEventListener('click', () => addToCart(id, name));
  prodContrainer.querySelectorAll('[class]').forEach(elem => {
    const prop = elem.className.split('-')[1];
    elem.id = `${prop}-${id}`;
    if (!product[prop]) return;

    elem.textContent = product[prop];
  });

  productsContainer.append(prodContrainer);

});


})();

