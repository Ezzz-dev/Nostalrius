function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32673, y = 32085, z = 08},430) and Game.isItemThere ({x = 32669, y = 32089, z = 08},430) and Game.isItemThere ({x = 32673, y = 32093, z = 08},430) and Game.isItemThere ({x = 32677, y = 32089, z = 08},430) and Game.isItemThere ({x = 32673, y = 32083, z = 08},3349) and Game.isItemThere ({x = 32667, y = 32089, z = 08},3585) and Game.isItemThere ({x = 32673, y = 32094, z = 08},3264) and Game.isItemThere ({x = 32679, y = 32089, z = 08},3059) then
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 32673, y = 32083, z = 08}, 3349)
		Game.removeItemOnMap({x = 32667, y = 32089, z = 08}, 3585)
		Game.removeItemOnMap({x = 32673, y = 32094, z = 08}, 3264)
		Game.removeItemOnMap({x = 32679, y = 32089, z = 08}, 3059)
		Game.sendMagicEffect({x = 32673, y = 32083, z = 08}, 11)
		Game.sendMagicEffect({x = 32667, y = 32089, z = 08}, 11)
		Game.sendMagicEffect({x = 32673, y = 32094, z = 08}, 11)
		Game.sendMagicEffect({x = 32679, y = 32089, z = 08}, 11)
		doRelocate({x = 32673, y = 32093, z = 08},{x = 32671, y = 32069, z = 08})
		doRelocate({x = 32669, y = 32089, z = 08},{x = 32672, y = 32069, z = 08})
		doRelocate({x = 32673, y = 32085, z = 08},{x = 32671, y = 32070, z = 08})
		doRelocate({x = 32677, y = 32089, z = 08},{x = 32672, y = 32070, z = 08})
		Game.sendMagicEffect({x = 32671, y = 32069, z = 08}, 11)
		Game.sendMagicEffect({x = 32672, y = 32069, z = 08}, 11)
		Game.sendMagicEffect({x = 32671, y = 32070, z = 08}, 11)
		Game.sendMagicEffect({x = 32672, y = 32070, z = 08}, 11)
	elseif item:getId() == 2773 then
		item:transform(2772, 1)
		item:decay()
	end
	return true
end