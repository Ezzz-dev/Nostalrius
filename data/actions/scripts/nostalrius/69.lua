function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2773 then
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32592, y = 32104, z = 14},{x = 32591, y = 32104, z = 14})
		doRelocate({x = 32592, y = 32105, z = 14},{x = 32591, y = 32105, z = 14})
		Game.createItem(1270, 1, {x = 32592, y = 32104, z = 14})
		Game.createItem(1270, 1, {x = 32592, y = 32105, z = 14})
		Game.createItem(1270, 1, {x = 32592, y = 32106, z = 14})
		Game.removeItemOnMap({x = 32593, y = 32103, z = 14}, 1271)
		Game.removeItemOnMap({x = 32594, y = 32103, z = 14}, 1271)
		Game.removeItemOnMap({x = 32595, y = 32103, z = 14}, 1271)
		Game.removeItemOnMap({x = 32596, y = 32103, z = 14}, 1271)
		Game.removeItemOnMap({x = 32597, y = 32103, z = 14}, 1271)
		Game.removeItemOnMap({x = 32598, y = 32103, z = 14}, 1271)
		Game.removeItemOnMap({x = 32599, y = 32103, z = 14}, 1271)
		Game.removeItemOnMap({x = 32600, y = 32103, z = 14}, 1271)
		Game.removeItemOnMap({x = 32601, y = 32103, z = 14}, 1271)
	end

	return true
end