function Tile.isItem(self)
	return false
end

function Tile.isContainer(self)
	return false
end

function Tile.isCreature(self)
	return false
end

function Tile.isPlayer(self)
	return false
end

function Tile.isTeleport(self)
	return false
end

function Tile.isTile(self)
	return true
end
