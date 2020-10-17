import * as jsonServer from 'json-server';
import * as routes from './routes.json';
// import middlewares from './middlewares';

const server = jsonServer.create();
const router = jsonServer.router('./db.json');
const port = 3002;

server.use(jsonServer.bodyParser);
server.use(jsonServer.rewriter(routes));
// server.use(middlewares);
server.use(router);
server.listen(port, () => {
  console.log(`JSON Server is running on port ${port}`);
});
