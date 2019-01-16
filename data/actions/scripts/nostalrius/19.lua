function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		item:remove()
		Game.createItem(2126, 1, {x = 32487, y = 31628, z = 13})
		Game.createItem(2126, 1, {x = 32487, y = 31629, z = 13})
		Game.createItem(2126, 1, {x = 32488, y = 31629, z = 13})
		Game.createItem(2126, 1, {x = 32487, y = 31627, z = 13})
		Game.createItem(2126, 1, {x = 32486, y = 31627, z = 13})
		Game.createItem(2126, 1, {x = 32486, y = 31628, z = 13})
		Game.createItem(2126, 1, {x = 32486, y = 31629, z = 13})
		Game.createItem(2126, 1, {x = 32486, y = 31630, z = 13})
		Game.createItem(2126, 1, {x = 32487, y = 31630, z = 13})
		Game.createItem(2126, 1, {x = 32488, y = 31630, z = 13})
		Game.createItem(2126, 1, {x = 32486, y = 31626, z = 13})
		Game.createItem(2126, 1, {x = 32487, y = 31626, z = 13})
		Game.createItem(2126, 1, {x = 32488, y = 31626, z = 13})
		Game.sendMagicEffect({x = 32488, y = 31628, z = 13}, 3)
	end
	return true
end