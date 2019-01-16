function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		item:remove()
		Game.removeItemOnMap({x = 32186, y = 31626, z = 08}, 2129)
		Game.removeItemOnMap({x = 32187, y = 31626, z = 08}, 2129)
		Game.removeItemOnMap({x = 32188, y = 31626, z = 08}, 2129)
		Game.removeItemOnMap({x = 32189, y = 31626, z = 08}, 2129)
		Game.sendMagicEffect({x = 32180, y = 31633, z = 08}, 3)
		Game.sendMagicEffect({x = 32186, y = 31626, z = 08}, 3)
		Game.sendMagicEffect({x = 32187, y = 31626, z = 08}, 3)
		Game.sendMagicEffect({x = 32188, y = 31626, z = 08}, 3)
		Game.sendMagicEffect({x = 32189, y = 31626, z = 08}, 3)
	end
	return true
end